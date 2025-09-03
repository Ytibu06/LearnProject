#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//进程间管道通信 : 管道通信：匿名管道pipe
//该程序演示了如何使用无名管道在父子进程之间进行通信

/**
 * 管道描述符：
 *      0：管道的读端
 *      1：管道的写端
 * (1) 管道是是单向通信的：父进程写，子进程读
 * (2) 管道的读写端通过打开文件的文件描述符进行传递，两个进程之间通信必须通过公共祖先来继承文件描述符,即：fork()之间创建管道符
 * (3) 父子进程之间通信必须通过管道符来传递数据，不能通过文件来传递数据
 * (4) 管道返回的文件描述符不同于打开文件的描述符
 * 
 */

 
int main(int argc, char *argv[] ){
    
    __pid_t pid;
    int pipefd[2]; // pipefd[0]用于读取，pipefd[1]用于写入

    //参数检查：确保程序运行时提供了必要的参数
    if(argc != 2){
        fprintf(stderr,"%s缺少参数", argv[0]);
        exit(EXIT_FAILURE);
    }

    //创建无名管道，pipefd[0]为读端，pipefd[1]为写端
    //如果创建成功，pipe()返回0；如果失败，返回-1
    if(pipe(pipefd) == -1){

        perror("pipe error");
        exit(EXIT_FAILURE);
    }


    //创建子进程，fork()会返回两次：
    //在父进程中返回子进程的PID，在子进程中返回0
    pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        //子进程逻辑：从管道中读取数据并输出到标准输出
        
        close(pipefd[1]); //子进程关闭写端
        char buf; //创建缓冲区存储从管道读取的数据
        
        char str[100] = {0};
        sprintf(str,"子进程: %d读取数据\n",getpid());
        write(STDOUT_FILENO, str, strlen(str));
        //循环读取管道中的数据，每次读取1个字节
        while(read(pipefd[0], &buf, 1) > 0){

            write(STDOUT_FILENO, &buf, 1); //将读取到的数据写入标准输出
        }
        write(STDOUT_FILENO, "\n", 1); //输出换行符
        close(pipefd[0]); //关闭读端
        printf("子进程: %d结束\n", getpid());

    }else{
        //父进程逻辑：将命令行参数写入管道
        
        close(pipefd[0]); //父进程关闭读端
        //数据写入管道
        printf("父进程: %d写入数据\n", getpid());
        write(pipefd[1], argv[1], strlen(argv[1])); //将命令行参数写入管道
        close(pipefd[1]); //关闭写端

        //等待子进程结束
        waitpid(pid,NULL,0); //注意：原代码中的witpid应为waitpid

    }

    return 0;
}