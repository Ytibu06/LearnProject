#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//使用互斥锁和条件变量实现生产者-消费者模式的多线程程序，包含一个固定大小的缓冲区和两个线程分别进行读写操作。


#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

// 初始化一个互斥锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//初始化条件变量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)   //写线程
{
    int i = 1;
    while (1){

        pthread_mutex_lock(&mutex); //使用共同的变量，使用互斥锁 ，获取锁
        if(count == BUFFER_SIZE){   //如果缓冲区已满，使用条件变量暂停当前线程
            pthread_cond_wait(&cond,&mutex);
        }

        buffer[count++] = i++;  //写入数据
        printf("write: %d\n", buffer[count-1]);
        pthread_cond_signal(&cond); //通知其他线程

        pthread_mutex_unlock(&mutex);   //释放锁

    }
    return NULL;
}

void *consumer(void *arg)    //读线程
{
    while (1){

        pthread_mutex_lock(&mutex); //使用共同的变量，使用互斥锁 ，获取锁
        if(count == 0){   //如果缓冲区已空，使用条件变量暂停当前线程
            pthread_cond_wait(&cond,&mutex);
        }
        printf("read: %d\n", buffer[--count]);
        pthread_mutex_unlock(&mutex);   //释放锁
        pthread_cond_signal(&cond);        

    }
    return NULL;
}


int main(int argc, char *argv[])
{
    //创建连个线程，一个进行写入buffer，一个读取buffer
    pthread_t producer_thread, consumer_thread;   //线程ID
    pthread_create(&producer_thread, NULL, producer, NULL);  //创建写入线程
    pthread_create(&consumer_thread, NULL, consumer, NULL);   //创建读取线程

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    printf("Producer-Consumer completed.\n");
    return 0;

}