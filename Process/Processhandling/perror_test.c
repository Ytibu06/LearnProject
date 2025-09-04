// 包含标准输入输出库头文件
#include <stdio.h>

// 主函数：演示perror函数的使用
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc, char const *argv[]){
    // 尝试打开一个不存在的文件，这会失败
    fopen("file.txt", "r");
    
    // 使用perror函数打印错误信息
    perror("Error opening file");
    return 0;
}