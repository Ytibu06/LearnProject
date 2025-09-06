#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 线程的退出：pthread_join


//接收结果的结构体
typedef struct Result{
    char *p;
    int len;
} Result;

void *red_thread(void *arg){
    Result *result = malloc(sizeof(Result));
    //解析传递的参数
    char code = *((char *)arg);

    char *buf = malloc(1024);   //声明缓冲区
    while(1){
        fgets(buf, 1024, stdin);
        if(buf[0] == code){
            free(buf);
            char *info = strdup("coderB thread exit");
            result->p = info;
            result->len = strlen(info);
            pthread_exit((void *)result); //线程退出
        }else{
            printf("%s", buf);

        }
    }
    
}
void *green_thread(void *arg){ 
    Result *result = malloc(sizeof(Result));
    //解析传递的参数
    char code = *((char *)arg);

    char *buf = malloc(1024);   //声明缓冲区
    while(1){
        fgets(buf, 1024, stdin);
        if(buf[0] == code){
            free(buf);
            char *info = strdup("coderB thread exit");
            result->p = info;
            result->len = strlen(info);
            pthread_exit((void *)result); //线程退出
        }else{
            printf("%s",buf);

        }
    }
}


int main(int argc, char *argv[]){

    pthread_t pid_red, pid_green;
    char red = 'r', green = 'g';
    Result *red_result = NULL, *green_result = NULL;

    pthread_create(&pid_red, NULL, (void *)red_thread, &red);
    pthread_create(&pid_green, NULL, (void *)green_thread, &green);
    
    //等待线程结束,释放资源：指针、结构体
    pthread_join(pid_red, (void **)&red_result);
    free(red_result->p);
    free(red_result);

    pthread_join(pid_green, (void **)&green_result);
    free(green_result->p);
    free(green_result);

    return 0;
}