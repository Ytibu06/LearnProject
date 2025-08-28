// 包含标准输入输出库头文件
#include <stdio.h>

// 主函数：演示fputs函数的使用
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc, const char *argv[] ){

    // 定义文件名
    char *filename = "io.txt";
    
    // 以追加和读取模式打开文件
    FILE *ioFile = fopen(filename,"a+");
    
    // 检查文件是否打开成功
    if(ioFile == NULL){
        printf("error  文件打开失败\n");
    }else
        printf("success 文件打开成功\n");


    /**
     * int fputs (const char *__restrict __s, FILE *__restrict __stream)
     * 函数功能：将字符串写入文件
     * 参数：
     * __s:写入的字符串
     * __stream:文件指针
     * 返回值：成功返回写入的字符数，失败返回EOF
     */

    // 将字符串写入文件
    int puts_result = fputs("love and love\n",ioFile);
    
    // 检查写入是否成功
    if(puts_result == EOF){
        printf("写入字符串失败\n");
    }else{
        printf("写入字符串成功\n");
    }


    // 关闭文件
    int result = fclose(ioFile);
    
    // 检查文件是否关闭成功
    if(result == EOF){
        printf("error 文件关闭失败\n");
    }else if(result == 0){
        printf("success 文件关闭成功\n");
    }

    return 0;
}