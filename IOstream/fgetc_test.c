// 包含标准输入输出库头文件
#include <stdio.h>

// 主函数：演示fgetc函数的使用
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
    * int fgetc(FILE *__stream)
    * 函数功能：从流中读取一个字符
    * 参数：
    *       __stream：文件指针
    * return : 读取的字符，如果到达文件末尾则返回EOF
    */

    // 从文件中读取第一个字符
    char c = fgetc(ioFile);
    printf("Read character: \n");
    
    // 循环读取文件中的所有字符，直到文件末尾
    while(c != EOF){
        printf("%c", c);
        c = fgetc(ioFile);
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