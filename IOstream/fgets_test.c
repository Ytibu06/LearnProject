#include <stdio.h>

int main(int argc, const char *argv[] ){

    FILE *ioFile = fopen("io.txt", "r");
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

    char buffer[100];
    printf("Read character: \n");
    while(fgets(buffer, sizeof(buffer), ioFile)){
        printf("%s", buffer);
    }
    printf("\n");


    int closeR = fclose(ioFile);
    if(closeR == EOF){
        printf("Error closing file\n");
    }

    return 0;
}

