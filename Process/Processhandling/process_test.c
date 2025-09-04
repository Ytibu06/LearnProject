// 包含标准输入输出库、标准库和unistd头文件
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// 定义全局变量num
int num = 0;

// 主函数：演示父子进程之间的内存独立性
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc, char const *argv)
{
    
    // 创建子进程
    __pid_t pid = fork();

    // 检查fork是否失败
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // 根据进程类型执行不同代码
    if(pid == 0){
        // 子进程代码段
        // 修改子进程中的num值
        num = 1;
        printf("子进程num值为%d\n",num);
    }else{
        // 父进程代码段
        // 睡眠1秒，确保子进程先执行完毕
        sleep(1);
        printf("父进程num值为%d\n",num);
    }
    
    return 0;
}