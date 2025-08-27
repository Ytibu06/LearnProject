#include <stdio.h>

int main(int argc, const char *argv[] ){

    FILE *ioFile = fopen("io.txt", "r");
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

    char c = fgetc(ioFile);
    printf("Read character: \n");
    while(c != EOF){
        printf("%c", c);
        c = fgetc(ioFile);
    }
    printf("\n");


    int closeR = fclose(ioFile);
    if(closeR == EOF){
        printf("Error closing file\n");
    }

    return 0;
}

