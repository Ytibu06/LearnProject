// 包含标准输入输出库和错误号头文件
#include <stdio.h>
#include <errno.h>


// 主函数：演示错误号的使用
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc, char **argv){

    // 尝试打开一个不存在的目录，这会失败
    fopen("/opt","a+");
    
    // 打印错误号
    printf("errno:%d\n",errno);
    
    // 使用perror函数打印错误信息
    perror("fopen");

    return 0;
}