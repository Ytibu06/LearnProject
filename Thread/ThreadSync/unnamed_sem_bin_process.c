#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>

//使用无名信号量解决进程间同步问题
//注意： sem_init()的第二个参数应设置为非零值；信号量必须置于共享内存区域，以确保多个进程都可以访问


int main()
{
    //定义共享内存名称和信号量的名称
    char *shm_value_name = "unnamed_sem_shm_value";
    char *shm_sem_name = "unnamed_sem_shm_sem";

    //创建共享内存对象
    int value_fd = shm_open(shm_value_name, O_CREAT | O_RDWR, 0664);    //创建共享内存对象
    int sem_fd = shm_open(shm_sem_name, O_CREAT | O_RDWR, 0664);        //创建信号量对象


    ftruncate(value_fd, sizeof(int));   //设置共享内存大小
    ftruncate(sem_fd, sizeof(sem_t));   //设置信号量的大小

    int *value = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, value_fd, 0);  //将共享内存对象映射到共享内存
    sem_t *sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, sem_fd, 0);  //将信号量对象映射到共享内存

    *value = 0; //初始化共享内存
    if (sem_init(sem, 1, 1) == -1) {    //注意 : 初始化信号量的时候，进程间第二个参数是1，线程间第二个参数是0
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    int pid = fork();

    if(pid > 0 ){
        sem_wait(sem);  //等待信号量
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;
        sem_post(sem);  //唤醒信号量

        //等待子进程结束
        waitpid(pid, NULL, 0);
        printf("parent process end\n");
        printf("value = %d\n", *value);

        if(sem_destroy(sem) == -1){
            perror("sem_destroy");
        }

        //解除共享内存的映射，关闭文件描述符，解除映射
        if(munmap(value, sizeof(int)) == -1){
            perror("munmap");
        }
        if(close(value_fd) == -1){
            perror("close value_fd");
        }

        //解除信号量的映射，关闭文件描述符，解除映射
        if(munmap(sem, sizeof(sem_t)) == -1){
            perror("munmap");
        }
        if(close(sem_fd) == -1){
            perror("close sem_fd");
        }

        //删除共享内存对象
        if(shm_unlink(shm_value_name) == -1){
            perror("shm_unlink");
        }
        //删除信号量对象
        if(shm_unlink(shm_sem_name) == -1){
            perror("shm_unlink");
        }

    }else if(pid == 0){
        sem_wait(sem);
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;
        sem_post(sem);
        
        if(munmap(value, sizeof(int)) == -1){
            perror("munmap");
        }
        if(close(value_fd) == -1){
            perror("close value_fd");
        }

        if(munmap(sem, sizeof(sem_t)) == -1){
            perror("munmap");
        }
        if(close(sem_fd) == -1){
            perror("close sem_fd");
        }
    }else{
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}