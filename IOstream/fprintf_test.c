#include <stdio.h>

int main(int argc, const char *argv[] ){

    char *filename = "io.txt";
    FILE *ioFile = fopen(filename,"a+");
    if(ioFile == NULL){
        printf("error  文件打开失败\n");
    }else
        printf("success 文件打开成功\n");


    /**
     * fprintf (FILE *__restrict __stream, const char *__restrict __fmt, ...)
     * 函数功能：将格式化的数据写入到流中。
     * 参数：
     *      __stream: 文件流
     *       __fmt: 格式字符串
     *       ...: 可变参数，填入格式化的长字符串
     * return : 成功返回写入的字符数，失败返回EOF
     */
    int printf_result = fprintf(ioFile,"%s %d %f %c %c %c\n","hello world",123,12.345, 'a', 'b', 'c');
    if(printf_result == EOF){
        printf("error 格式化字符串写入失败\n");
    }else
        printf("success 格式化字符串%d写入成功\n",printf_result);


    int result = fclose(ioFile);
    if(result == EOF){
        printf("error 文件关闭失败\n");
    }else if(result == 0){
        printf("success 文件关闭成功\n");
    }

    return 0;
}