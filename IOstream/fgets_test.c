// 包含标准输入输出库头文件
#include <stdio.h>

// 主函数：演示fgets函数的使用
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc, const char *argv[] ){

    // 以只读模式打开io.txt文件
    FILE *ioFile = fopen("io.txt", "r");
    
    // 检查文件是否打开成功
    if(ioFile == NULL){
        printf("Error opening file\n");
    }

   /**
    * char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
    *  函数功能：从流中读取一行，并保存在字符串 __s 中
    *  参数 ：
    *       __s: 要读取的字符串
    *       __n: 最多读取的字符数
    *       __stream: 文件流
    *  return ：
    *       读取的字符数，如果返回值为 NULL，则表示读取失败
    */

    // 定义缓冲区用于存储读取的字符串
    char buffer[100];
    printf("Read character: \n");
    
    // 循环读取文件中的每一行，直到文件末尾
    while(fgets(buffer, sizeof(buffer), ioFile)){
        printf("%s", buffer);
    }
    printf("\n");

    // 关闭文件
    int closeR = fclose(ioFile);
    
    // 检查文件是否关闭成功
    if(closeR == EOF){
        printf("Error closing file\n");
    }

    return 0;
}