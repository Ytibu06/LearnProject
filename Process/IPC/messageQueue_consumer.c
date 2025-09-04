#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define CLOCK_REALTIME 0

int main(int argc, char *argv[]){
    
    // 定义消息队列属性结构体，用于设置消息队列的各种参数
    struct mq_attr attr;
    // 设置单条消息的最大字节数为128字节
    attr.mq_msgsize = 128;
    // 设置消息队列最多能容纳的消息数量为10条
    attr.mq_maxmsg = 10;
    // 设置消息队列标志位，0表示阻塞模式
    attr.mq_flags = 0;
    // 当前消息队列中的消息数量，初始化为0
    attr.mq_curmsgs = 0;
    
    // 定义消息队列名称，以'/'开头是POSIX消息队列的命名规范
    char *mq_name = "/p_c_mq";
    // 创建或打开消息队列，O_CREAT表示不存在则创建，O_RDWR表示可读可写
    // 0666设置访问权限，&attr传递消息队列属性参数
    mqd_t mqdes = mq_open(mq_name, O_CREAT | O_RDWR, 0666, &attr);

    // 检查消息队列是否创建成功，失败返回(mqd_t)-1
    if(mqdes == (mqd_t)-1){
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // 定义输入缓冲区，用于存储从控制台读取的数据
    // 修改: 将缓冲区大小从128改为129，确保能容纳128字节的消息内容加上可能的结束符
    char buf[128];
    // 定义时间结构体，用于设置消息的超时时间
    struct timespec time_info;
    
    // 无限循环，持续接收用户输入
    while(1){
        // 清空缓冲区，确保没有残留数据
        memset(buf, 0, sizeof(buf));
        // 获取当前时间，并设置5秒后超时
        clock_gettime(CLOCK_REALTIME, &time_info);
        time_info.tv_sec += 5;
        
        // 修改: 添加对mq_timedreceive返回值的检查，处理超时情况
        ssize_t bytes_received = mq_timedreceive(mqdes, buf, sizeof(buf), NULL, &time_info);
        if(bytes_received == -1){
            perror("mq_timedreceive");
            // 超时或其他错误时继续循环而不是退出
            continue;
        }
        //判断当前数据是否为EOF，如果是则跳出循环
        // 修改: 检查消息内容而不是检查buf[0]是否为EOF
        if(strcmp(buf, "EXIT") == 0){
            printf("Received EXIT message, exiting...\n");
            break;
        }
        printf("receive message: %s\n", buf);
        printf("send message end\n");
    }

    //关闭消息队列描述符
    close(mqdes);
    //清除消息队列
    mq_unlink(mq_name);

    return 0;
}