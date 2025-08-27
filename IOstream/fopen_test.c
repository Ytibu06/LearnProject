#include <stdio.h>

int main(int argc, char const *argv[]){

    /**
     * FILE *fopen (const char *__restrict __filename,
		    const char *__restrict __modes)
     * const char *__restrict __filename: 字符串表示要打开的文件名称
     * const char *__restrict __modes:    访问模式
            r : 只读，不存在报错
            w : 只写，清空或创建文件
            a : 追加写，追加写或创建文件
            r+ : 读写，必须存在，覆盖写
            w+ : 读写，清空或创建
            a+ : 追加读写，追加写或创建
        return : FILE* 结构体指针 表示一个文件
            报错返回NULL
     */

    char *filename = "io.txt";
    FILE *ioFile = fopen(filename,"a+");
    
    if(ioFile == NULL){
        printf("error  文件打开失败\n");
    }else
        printf("success 文件打开成功\n");


    return 0;

}