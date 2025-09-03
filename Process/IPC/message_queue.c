#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//进程间通信：消息队列messageQueue


int main(int argc, char *argv[]){

    //创建消息队列
    struct mq_attr attr;
    //重要参数 : 表示消息队列容量
    attr.mq_msgsize = 128;
    attr.mq_maxmsg = 10;
    //被忽略消息
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
    
    char *mq_name = "/fater_son";
    mqd_t mqdes = mq_open(mq_name, O_CREAT | O_RDWR, 0666, &attr);

    if(mqdes == (mqd_t)-1){
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    //创建父子进程
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){   //子进程：等待接收消息队列中的消息
        // 关闭子进程中的写端（可选优化）
        mq_close(mqdes);
        mqdes = mq_open(mq_name, O_RDONLY, 0666, NULL);

        char buf[128];  // 缓冲区大小应与mq_msgsize一致
        struct timespec time_info;
        for (size_t i = 0; i < 10; i++)
        {
            //清空缓冲区
            memset(buf, 0, sizeof(buf));

            //设置接收时间  CLOCK_REALTIME  = 0
            clock_gettime(0, &time_info);
            time_info.tv_sec += 15;

            //接收消息,打印到控制台
            ssize_t bytes_received = mq_timedreceive(mqdes, buf, sizeof(buf), NULL, &time_info);
            if (bytes_received == -1){
                perror("mq_timedreceive");
            } else {
                printf("Receive message: %s\n", buf);
            }
        }
        
        // 子进程关闭消息队列描述符
        mq_close(mqdes);
        
    }else{  //父进程:发送消息到队列中
        // 关闭父进程中的读端（可选优化）
        mq_close(mqdes);
        mqdes = mq_open(mq_name, O_WRONLY, 0666, NULL);
        
        char send_buf[128];  // 缓冲区大小应与mq_msgsize一致
        struct timespec time_info;

        for (size_t i = 0; i < 10; i++)
        {
            //清空buf
            memset(send_buf, 0, sizeof(send_buf));
            
            //获取当前时间 CLOCK_REALTIME = 0
            clock_gettime(0, &time_info);
            
            // 使用正确的时间值构建消息
            sprintf(send_buf, "hello, %ld", time_info.tv_sec);
            
            //发送消息
            if(mq_timedsend(mqdes, send_buf, strlen(send_buf), 0, &time_info) == -1){
                perror("mq_timedsend");
            }
            printf("send message: %s\n", send_buf);
            sleep(1);
        }
        
        // 等待子进程完成
        wait(NULL);
        
        // 父进程关闭消息队列描述符并清除消息队列
        mq_close(mqdes);
        mq_unlink(mq_name);
    }

    return 0;
}