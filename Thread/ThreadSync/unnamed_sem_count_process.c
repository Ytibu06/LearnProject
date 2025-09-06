#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

//无名信号量 作为计数信号量实现 进程间通信


int main(int argc, char *argv[])
{
    char *name = "unnamed_sem_count";
    
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);    //创建一个共享内存

    ftruncate(fd,sizeof(sem_t));

    sem_t *sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_init(sem, 1, 0);
    
    pid_t pid = fork();

    if(pid < 0){
        perror("fork");

    }else if(pid == 0){
        sleep(1);
        printf("child process\n");
        sem_post(sem);
    }else{
        sem_wait(sem);
        printf("parent process\n");
        waitpid(pid, NULL, 0);
    }

    if(pid > 0){
        if(sem_destroy(sem) == -1){
            perror("sem_destroy");
        }
    }

    if(munmap(sem, sizeof(sem_t)) == -1){
        perror("munmap");
    }
    if(close(fd) == -1){
        perror("close_fd");
    }

    if(pid > 0){
        if(shm_unlink(name) == -1){
            perror("shm_unlink");
        }
    }

    return 0;


}