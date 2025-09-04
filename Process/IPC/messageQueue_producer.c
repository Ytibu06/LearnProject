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
    // 修改: 保持缓冲区大小为128字节，与消息队列配置匹配
    char buf[128];
    // 定义时间结构体，用于设置消息的超时时间
    struct timespec time_info;
    
    // 无限循环，持续接收用户输入
    while(1){
        // 清空缓冲区，确保没有残留数据
        memset(buf, 0, sizeof(buf));
        // 从标准输入(STDIN_FILENO即文件描述符0)读取数据到buf中
        // read函数返回实际读取的字节数
        ssize_t read_count = read(STDIN_FILENO, buf, sizeof(buf)-1);
        // 获取当前时间，并设置5秒后超时
        clock_gettime(CLOCK_REALTIME, &time_info);
        time_info.tv_sec += 5;
        
        // 检查读取是否出错
        if(read_count == -1){
            perror("read");
            continue;  // 出错则跳过本次循环，继续下一次读取
        
        // 检查是否读到文件末尾(EOF)
        }else if(read_count == 0){
            printf("EOF,exit...\n");
            // 修改: 发送"EXIT"消息而不是单个EOF字符
            char exit_msg[] = "EXIT";
            // 发送EOF消息到消息队列，通知接收端结束
            // mq_timesend带超时机制，&time_info指定超时时间
            if(mq_timedsend(mqdes, exit_msg, strlen(exit_msg), 0, &time_info) == -1){
                perror("mq_timesend");
            }
            break;
        }
        // 修改: 确保字符串正确结束
        buf[read_count] = '\0';
        if(mq_timedsend(mqdes, buf, strlen(buf), 0, &time_info) == -1){
            perror("mq_timesend");
        }
        printf("send message end\n");
    }

    //关闭消息队列描述符
    close(mqdes);
    //清除消息队列
    //mq_unlink(mq_name);

    return 0;
}