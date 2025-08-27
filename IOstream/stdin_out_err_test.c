#include <stdio.h>
#include <stdlib.h>

int main(){
    
    char *ch = malloc(100);
    //标准输入
    fgets(ch, 10, stdin);
    printf("你好：%s\n", ch);

    //标准输出
    fputs(ch,stdout);
    printf("\n");

    //错误输出
    fputs(ch,stderr);
    printf("\n");

    return 0;
}