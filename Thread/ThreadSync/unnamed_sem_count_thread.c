#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//无名信号量 作为计数信号量控制线程执行顺序 实现线程间通信


sem_t *full;
sem_t *empty;

int shared_num;

int rand_num(){
    srand(time(NULL));
    return rand();
}

void *producer(void *arg)
{
    for (size_t i = 1; i <= 5; i++)
    {
        sem_wait(empty);
        printf("producer: %zu\n", i);
        sleep(1);
        shared_num = rand_num();
        sem_post(full);
    }
    
}

void *consumer(void *arg)
{
    for (size_t i = 1; i <= 5; i++)
    {
        sem_wait(full);
        printf("consumer: %zu\n", i);
        sleep(1);
        printf("consumer: %d\n", shared_num);
        shared_num = rand_num();
        sem_post(empty);
    }
}

int main()
{
    full  = malloc(sizeof(sem_t)); 
    empty = malloc(sizeof(sem_t));

    //初始化信号量
    sem_init(full,0,0);
    sem_init(empty,0,1);

    //创建线程
    pthread_t producer_id, consumer_id;
    pthread_create(&producer_id, NULL, (void *)producer, NULL);
    pthread_create(&consumer_id, NULL, (void *)consumer, NULL);

    //阻塞线程
    pthread_join(producer_id, NULL);
    pthread_join(consumer_id, NULL);

    //销毁信号量
    sem_destroy(full);
    sem_destroy(empty);

    return 0;
}