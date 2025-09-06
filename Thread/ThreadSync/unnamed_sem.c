#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//无名信号量 ： 
/**
 * sem_init(sem_t *sem, int pshared, unsigned int value);
 * 参数：
 *      sem：信号量的指针
 *      pshared：信号量的属性，0表示进程内，1表示进程间
 *      value：信号量的初始值
 * 返回值：
 *      成功返回0，失败返回-1
 */

sem_t unnamed_sem;
int shared_num = 0;


void *plusOne(void *arg){
    sem_wait(&unnamed_sem);
    int temp = shared_num + 1;
    shared_num = temp;
    sem_post(&unnamed_sem);
}

int main(int argc, char *argv[])
{
    sem_init(&unnamed_sem, 0, 1);

    pthread_t tid[10000];

    for(int i = 0; i < 10000; i++){
        pthread_create(&tid[i], NULL, plusOne, NULL);
    }

    for(int i = 0; i < 10000; i++){
        pthread_join(tid[i], NULL);
    }

    printf("shared_num = %d\n", shared_num);
    
    return 0;
}