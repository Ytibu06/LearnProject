#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_LEN 1024


//创建线程 : 创建两个线程，一个线程读取控制台信息，写入缓冲buf，一个线程读取缓冲buf

/**
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
 * 函数功能 : 创建线程
 * 参数说明 :
 *      thread : 线程ID
 *      attr : 线程属性
 *      start_routine : 线程执行函数
 *      arg : 线程执行函数的参数
 * 返回值 : 成功返回0，失败返回错误码
 */


char *buf;

//写线程的执行函数
void *intput_thread(void *arg)
{
    while(1){
        fgets(buf, BUF_LEN, stdin);
    }
    return NULL;
}

//读线程的执行函数
void *output_thread(void *arg)
{
    int i = 0;
    while(1){
        if(buf[i]){
            fputc(buf[i], stdout);
            fputc('\n', stdout);
            //i++;
            buf[i++] = 0;
            if(i >= BUF_LEN){
                i = 0;
            }
        }else{
            sleep(1);
        }
        
    }
    return NULL;
}

int main(int argc, char *argv[]){

    buf = (char *)malloc(BUF_LEN);
    //声明线程id
    pthread_t pid_input, pid_output;

    //创建线程
    pthread_create(&pid_input, NULL, (void *)intput_thread, NULL);  //读线程
    pthread_create(&pid_output, NULL, (void *)output_thread, NULL); //写线程

    //主线程等待两个线程结束
    pthread_join(pid_input, NULL);
    pthread_join(pid_output, NULL);

    free(buf);

    return 0;
}