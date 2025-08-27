#include <stdio.h>

int main(int argc, char const *argv[]){

    char *filename = "io.txt";
    FILE *ioFile = fopen(filename,"a+");
    if(ioFile == NULL){
        printf("error  文件打开失败\n");
    }else
        printf("success 文件打开成功\n");

    /**
     * int fclose (FILE *__stream) __nonnull ((1));
     * FILE *__stream : 关闭的文件
     * return : 成功返回0 失败返回EOF(负数) 通常关闭失败会直接报错
     */

    int result = fclose(ioFile);
    if(result == EOF){
        printf("error 文件关闭失败\n");
    }else if(result == 0){
        printf("success 文件关闭成功\n");
    }


    return 0;

}