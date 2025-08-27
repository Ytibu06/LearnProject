#include <stdio.h>

int main(int argc, const char *argv[] ){


    //文件打开
    FILE *ioFile = fopen("user.txt", "r");
    if(ioFile == NULL){
        printf("Error opening file\n");
    }

   /**
    * int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...)
    * 函数功能 ：从流中读取数据
    * 参数 ：
    *       __stream ：文件流指针
    *       __format ：格式控制字符串
    *       ... ：可变参数，格式化的字符串
    * 返回值 ：成功返回读取的字符数，失败返回0 错误返回EOF
    */

    //文件格式化读取
    char name[50];
    int age;
    char wife[50];
    int scanfR;

    //int scanfR = fscanf(ioFile, "%s %d %s", name,&age,wife);
    // if(scanfR != EOF){
    //     printf("name: %s age: %d wife: %s",name, age, wife);
    // }

    while((scanfR = fscanf(ioFile, "%s %d %s", name,&age,wife)) != EOF){
        printf("name: %s age: %d wife: %s\n",name, age, wife);
    }

    //文件关闭
    int closeR = fclose(ioFile);
    if(closeR == EOF){
        printf("Error closing file\n");
    }

    return 0;
}

