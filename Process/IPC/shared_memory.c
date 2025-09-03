#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

//进程间通信方式：共享内存

/**
 * int shm_open(const char *__name, int __oflag, mode_t __mode)
 * Open shared memory segment.
 */

int main(int argc, char *argv[]){
    
    //创建共享内存对象
    char shm_name[100] = {0};
    sprintf(shm_name, "/letter%d", getpid());

    int fd;
    fd = shm_open(shm_name,O_RDWR | O_CREAT, 0644);
    if(fd < 0){
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    //设置共享内存大小
    ftruncate(fd, 1024);

    //内存映射
    char *share = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    //映射失败提示
    if(share == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    //映射完成关闭连接
    close(fd);

    //使用内存映射实现进程间通讯
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){ //子进程代码
        strcpy(share,"hello world");
        printf("子进程:%d开辟通信！\n",getpid());
    }else{  //父进程代码
        waitpid(pid,NULL,0);
        printf("父进程：%d完成父进程%d的通信回复：%s！\n",getpid(),pid,share);

        //释放映射区
        int ret = munmap(share,1024);
        if(ret == -1){
            perror("munmap");
            exit(EXIT_FAILURE);
        }
    }

    //释放映射区
    //释放共享内存对象
    shm_unlink(shm_name);
    
    return 0;
}