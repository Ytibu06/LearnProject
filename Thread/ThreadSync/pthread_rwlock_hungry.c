#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 读写锁 写饥饿机制rwlock_hungry : 写锁必须等待所有读全部完成后才会执行写,初始读写锁属性，确保写优先(系统默认读优先)

pthread_rwlock_t rwlock;  // 定义一个读写锁变量
int shared_data = 0;      // 定义一个共享数据变量，将被多个线程访问

// 写者线程函数：负责修改共享数据
// 每个写者线程会将shared_data的值增加1
void *lock_writer(void *arg)
{ 
    // 获取写锁，确保独占访问共享数据
    pthread_rwlock_wrlock(&rwlock);
    
    // 读取当前值并增加1
    int tmp = shared_data + 1;
    
    // 模拟处理时间，让线程睡眠1秒
    sleep(1);
    
    // 将新值写回共享数据
    shared_data = tmp;
    
    // 打印写入后的值
    printf("writer: %d\n", shared_data);
    
    // 释放写锁，允许其他线程访问
    pthread_rwlock_unlock(&rwlock);
    
    return NULL;
}

// 读者线程函数：负责读取共享数据
// 多个读者可以同时读取共享数据
void *lock_reader(void *arg)
{
    // 获取读锁，允许多个读者同时访问
    pthread_rwlock_rdlock(&rwlock);
    
    // 读取并打印当前共享数据的值
    printf("reader: %d\n", shared_data);
    
    // 释放读锁
    pthread_rwlock_unlock(&rwlock);
    
    return NULL;
}

int main(int argc, char *argv[])
{
    //初始化读写锁属性
    pthread_rwlockattr_t attr;  // 定义一个读写锁属性变量
    pthread_rwlockattr_init(&attr); // 初始化读写锁属性
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP); // 设置读写锁属性为写优先
    // 显式初始化读写锁
    // PTHREAD_RWLOCK_INITIALIZER也可以用于静态初始化
    pthread_rwlock_init(&rwlock, &attr);

    // 声明线程变量：2个写者线程，6个读者线程
    pthread_t writer1, writer2, reader1, reader2, reader3, reader4, reader5, reader6;

    // 创建写者线程
    // 注意：传递给线程函数的参数应该是void*类型
    pthread_create(&writer1, NULL, lock_writer, (void*)"writer1");
    pthread_create(&reader1, NULL, lock_reader, (void*)"reader1");
    pthread_create(&reader2, NULL, lock_reader, (void*)"reader2");
    pthread_create(&reader3, NULL, lock_reader, (void*)"reader3");


    // 主线程睡眠3秒，确保写者线程完成写操作
    //sleep(3);

    // 创建读者线程
    pthread_create(&writer2, NULL, lock_writer, (void*)"writer2");    
    pthread_create(&reader4, NULL, lock_reader, (void*)"reader4");
    pthread_create(&reader5, NULL, lock_reader, (void*)"reader5");
    pthread_create(&reader6, NULL, lock_reader, (void*)"reader6");

    // 等待所有线程结束
    // 写者线程需要先于读者线程结束，否则可能出现竞争条件
    pthread_join(writer1, NULL);
    pthread_join(writer2, NULL);
    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);
    pthread_join(reader3, NULL);    
    pthread_join(reader4, NULL);
    pthread_join(reader5, NULL);
    pthread_join(reader6, NULL);

    // 销毁读写锁，释放相关资源
    pthread_rwlock_destroy(&rwlock);
    
    return 0;
}
