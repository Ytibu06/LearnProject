// 包含标准输入输出库、unistd库和标准库头文件
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 主函数：简单的进程测试程序
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc , const char *argv[] ){

    // 检查命令行参数是否足够
    if(argc < 2){
        printf("argc not enough\n");
        return 1;
    }
    
    // 打印进程启动信息
    printf("%s进程 : %d启动\n",argv[1], getpid());

    return 0;
}