#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//线程锁：互斥锁mutex


#define THREAD_COUNT 20000
// 初始化互斥锁
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *add_thread(void *arg){

    int * p = (int *)arg;

    //累计之前获取锁保证只有一个线程进行操作
    pthread_mutex_lock(&counter_mutex);
    (*p)++;
    //累加完成之后释放锁
    pthread_mutex_unlock(&counter_mutex);

    return (void *)0;
}
int main(int argc, char *argv[]){

    pthread_t pid[THREAD_COUNT];
    int num = 0;

    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(pid+i,NULL,add_thread,&num);
    }

    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(pid[i],NULL);
    }
    
    printf("num = %d\n",num);
    

    return 0;
}
