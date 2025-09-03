#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

//进程间通信方式：进程间共享数据内存对象的数据存储


int main(int argc, char *argv[]){

    char shm_name[100] = {0};
    sprintf(shm_name, "/my_shared_memory%d", getpid());
    int fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if(fd < 0){
        perror("shm_open");
        exit(1);
    }

    while (1)
    {
        /* code */
    }
    

    return 0;
}