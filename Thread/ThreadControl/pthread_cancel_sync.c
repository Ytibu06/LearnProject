#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 线程的退出：pthread_cancel的异步取消

void *thread_func(void *arg){
    printf("thread_start: \n");
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

    int i = 0;
    while (1)
    {
        printf("%d\n",i++);
    }
    
    printf("thread_end: %d\n", getpid());
    return NULL;
}


int main(int argc, char *argv[]){
    
    //创建线程
    pthread_t tid;
    pthread_create(&tid, NULL,thread_func, NULL);

    if(pthread_cancel(tid) != 0){
        perror("pthread_detach");
    }

    void *res;
    pthread_join(tid, &res);

    if(res == PTHREAD_CANCELED){
        printf("thread_join_end: %d\n", getpid());
    }else{
        printf("thread_join: %d\n", getpid());
    }


    return 0;
}