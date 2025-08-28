// 包含标准输入输出库头文件
#include <stdio.h>

// 主函数：演示fputc函数的使用
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
     * int fputc (int __c, FILE *__stream) __nonnull ((2));
     * int _c : ASCII 码对应的char
     * FILE *_stream : 文件指针
     * return : 成功返回写入的字符，失败返回EOF
     * 读写权限记录在fopen()中的参数中
     */

    // 将字符'a'(ASCII码为97)写入文件
    int put_result = fputc(97,ioFile);
    
    // 检查写入是否成功
    if(put_result == EOF){
        printf("写入文件失败\n");
    }else{
        printf("写入%c成功\n",put_result);
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