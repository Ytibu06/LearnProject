// 包含系统状态、标准输入输出、标准库、unistd、文件控制和字符串操作头文件
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


// 主函数：演示父子进程共享文件描述符
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc, char *argv[])
{
    
    //fork()之前
    //打开一个文件用于写入
    int fd = open("io.txt", O_CREAT | O_WRONLY | O_APPEND ,0664);

    // 检查文件是否打开成功
    if(fd == -1){
        perror("open : ");
        exit(EXIT_FAILURE);
    }

    // 定义缓冲区
    char buffer[1024];
    
    // 创建子进程
    pid_t pid = fork();

    // 检查fork是否失败
    if(pid<0){
        perror("fork : ");
    }else if(pid == 0){
        //子进程代码段
        // 将子进程信息复制到缓冲区
        strcpy(buffer,"child process write to file\n");
        printf("child process write to file\n");
    }else{  
        //父进程代码段
        // 将父进程信息复制到缓冲区
        strcpy(buffer,"parent process write to file\n");
        printf("parent process write to file\n");
    }

    // 将缓冲区内容写入文件
    ssize_t bytes = write(fd,buffer,strlen(buffer));
    printf("write bytes : %ld\n",bytes);

    // 检查写入是否成功
    if(bytes == -1){
        perror("write : ");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 关闭文件描述符
    close(fd);

    // 根据进程类型打印结束信息
    if(pid == 0){
        printf("child process write end\n");
    }else{
        printf("parent process write end\n");
    }
    
    return 0;
}