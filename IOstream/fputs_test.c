#include <stdio.h>

int main(int argc, const char *argv[] ){

    char *filename = "io.txt";
    FILE *ioFile = fopen(filename,"a+");
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

    int puts_result = fputs("love and love\n",ioFile);
    if(puts_result == EOF){
        printf("写入字符串失败\n");
    }else{
        printf("写入字符串成功\n");
    }


    int result = fclose(ioFile);
    if(result == EOF){
        printf("error 文件关闭失败\n");
    }else if(result == 0){
        printf("success 文件关闭成功\n");
    }

    return 0;
}