#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//进程通信 : 信号处理器signal

//信号处理函数
void sigint_handler(int signo){
    printf("receive signal %d\n", signo);
    exit(signo);
}
int main(int argc, char *argv[]){

    //信号的注册
    if (signal(SIGINT, sigint_handler) == SIG_ERR){
        perror("signal");
        exit(1);
    }

    while(1){
        sleep(1);
        printf("running...\n");
    }

    return 0;
}