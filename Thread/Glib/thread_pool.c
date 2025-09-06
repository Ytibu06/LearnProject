#include <glib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//线程池glib的使用案例

#define MAX_THREADS 10

void *task_func(gpointer data, gpointer user_date){
    int task_num = *(int *)data;
    free(data);
    printf("task_func: %d\n", task_num);
    sleep(task_num);
    printf("task_func: %d finish\n", task_num);
    return NULL;
}
int main()
{

    //创建线程池
    GThreadPool *pool = g_thread_poll_new(task_func, NULL, MAX_THREADS, TRUE,NULL);
    
    //添加任务
    for (size_t i = 0; i < 10; i++)
    {
        int *tmp = malloc(sizeof(int));

        *tmp = i + 1;

        g_thread_poll_push(pool, tmp);
    }
    
    g_thread_poll_free(pool,FALSE,TRUE);
    printf("main thread exit\n");

    return 0;
}