#include <stdio.h>

int main(int argc, const char *argv[] ){

    char *filename = "io.txt";
    FILE *ioFile = fopen(filename,"a+");
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

    int put_result = fputc(97,ioFile);
    if(put_result == EOF){
        printf("写入文件失败\n");
    }else{
        printf("写入%c成功\n",put_result);
    }


    int result = fclose(ioFile);
    if(result == EOF){
        printf("error 文件关闭失败\n");
    }else if(result == 0){
        printf("success 文件关闭成功\n");
    }

    return 0;
}