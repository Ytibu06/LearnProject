#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[])
{
    
    //fork()之前
    //打开一个文件
    int fd = open("io.txt", O_CREAT | O_WRONLY | O_APPEND ,0664);

    if(fd == -1){
        perror("open : ");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    pid_t pid = fork();

    if(pid<0){
        perror("fork : ");
    }else if(pid == 0){
        //子进程代码
        strcpy(buffer,"child process write to file\n");
        printf("child process write to file\n");
    }else{  
        //父进程代码
        //sleep(1);
        strcpy(buffer,"parent process write to file\n");
        printf("parent process write to file\n");
    }

    ssize_t bytes = write(fd,buffer,strlen(buffer));
    printf("write bytes : %ld\n",bytes);

    if(bytes == -1){
        perror("write : ");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    if(pid == 0){
        printf("child process write end\n");
    }else{
        printf("parent process write end\n");
    }
    
    return 0;
}