#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//无名信号量实现互斥锁功能
//int sem_init (sem_t *__sem, int __pshared, unsigned int __value);

/**
 * @brief 初始化一个未命名的 POSIX 信号量
 * 
 * `sem_init` 函数用于初始化由 `__sem` 指向的信号量对象，并将其计数器设置为 `__value` 指定的初始值。
 * 信号量是一种同步原语，常用于控制对共享资源的访问或线程间的同步。
 * 
 * 此函数创建的是未命名信号量，与通过 `sem_open` 创建的命名信号量不同。
 * 
 * @param __sem 指向要初始化的 `sem_t` 类型信号量对象的指针。该对象必须是用户分配的有效的未初始化内存。
 * @param __pshared 控制信号量的共享范围：
 *   - 若值为 0：信号量仅在当前进程内的线程间共享，不能在进程间使用
 *   - 若值非 0：信号量在多个进程间共享（需要在共享内存中分配），但具体实现可能不支持此特性
 * @param __value 信号量的初始计数值，表示可用资源的数量。该值必须满足以下条件：
 *   - 必须大于等于 0
 *   - 必须小于等于系统定义的最大值 SEM_VALUE_MAX（通常为 32767）
 * 
 * @return 执行结果：
 *   - 成功时返回 0，此时信号量已成功初始化，可以正常使用
 *   - 失败时返回 -1，并设置 `errno` 来指示具体的错误原因
 * 
 * @error EINVAL 参数 `__value` 超过了系统允许的最大值 SEM_VALUE_MAX
 * @error ENOSYS 参数 `__pshared` 非零，但当前系统不支持进程间共享的信号量
 * @error ENOMEM 系统资源不足，无法完成初始化
 * 
 * @note
 * - 调用此函数前，`__sem` 指向的内存必须未被初始化过。重复初始化同一个信号量会导致未定义行为。
 * - 使用完毕后，必须调用 `sem_destroy` 函数来释放信号量相关的资源。
 * - 如果信号量需要在多个进程间共享，`__sem` 指向的内存必须放在共享内存区域中。
 * - 信号量的初始值通常表示可用资源的数量：0 表示资源不可用，正数表示可用资源数量。
 * 
 * @warning
 * - 不要对已经初始化的信号量再次调用此函数
 * - 多进程共享的信号量需要特殊配置共享内存，不是所有系统都支持
 * 
 * @example
 *   sem_t my_semaphore;
 *   // 初始化为 1，常用于互斥访问（二进制信号量）
 *   if (sem_init(&my_semaphore, 0, 1) == -1) {
 *       perror("sem_init failed");
 *       return -1;
 *   }
 *   // 使用信号量...
 *   sem_destroy(&my_semaphore); // 清理资源
 * 
 * @see sem_destroy(), sem_wait(), sem_post(), sem_open()
 */

sem_t unnamed_sem;
int shared_num = 0;


void *plusOne(void *arg)
{
    sem_wait(&unnamed_sem);     // 获取信号量
    int temp = shared_num + 1;
    shared_num = temp;
    sem_post(&unnamed_sem);     // 释放信号量
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

    int des_r = sem_destroy(&unnamed_sem);  // 释放信号量资源
    if(des_r != 0){
        perror("sem_destroy");
    }
    
    return 0;
}