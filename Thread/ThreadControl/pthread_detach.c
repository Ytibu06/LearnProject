#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 线程的退出：pthread_detach


void *thread_func(void *arg){
    printf("thread_func: %d\n", getpid());
    sleep(2);
    printf("thread_func: %d\n", getpid());
    return NULL;
}

int main(int argc, char *argv[]){
    
    //创建线程
    pthread_t tid;
    pthread_create(&tid, NULL,&thread_func, NULL);

    //使用detach标记等待线程完成之后进行资源回收
    pthread_detach(tid);

    printf("main continus: %d\n", getpid());
    //主线程运行完成比子线程运行更久
    sleep(5);
    printf("main end: %d\n", getpid());


    return 0;
}