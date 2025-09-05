#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

// 初始化一个互斥锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//初始化条件变量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *write_buffer(void *arg)   //写线程
{
    int i = 0;
    while (i < 20){  // 限制写入次数，避免无限循环
        pthread_mutex_lock(&mutex); //使用共同的变量，使用互斥锁 ，获取锁
        while(count == BUFFER_SIZE){   //如果缓冲区已满，使用条件变量暂停当前线程
            pthread_cond_wait(&cond,&mutex);
        }
        buffer[count++] = i++;  //写入数据
        printf("write: %d\n", buffer[count-1]);
        pthread_cond_signal(&cond); //通知其他线程

        pthread_mutex_unlock(&mutex);   //释放锁
        usleep(100000); // 添加延迟，便于观察
    }
    return NULL;
}

void *read_buffer(void *arg)    //读线程
{
    int read_count = 0;
    while (read_count < 20){  // 限制读取次数，与写入次数匹配
        pthread_mutex_lock(&mutex); //使用共同的变量，使用互斥锁 ，获取锁
        while(count == 0){   //如果缓冲区已空，使用条件变量暂停当前线程
            pthread_cond_wait(&cond,&mutex);
        }
        printf("read: %d\n", buffer[--count]);
        read_count++;
        pthread_mutex_unlock(&mutex);   //释放锁  // 修复：添加缺失的解锁
        pthread_cond_signal(&cond);        
        usleep(150000); // 添加延迟，便于观察
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    //创建连个线程，一个进行写入buffer，一个读取buffer
    pthread_t t1, t2;   //线程ID
    pthread_create(&t1, NULL, write_buffer, NULL);  //创建写入线程
    pthread_create(&t2, NULL, read_buffer, NULL);   //创建读取线程

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Producer-Consumer completed.\n");
    return 0;

}