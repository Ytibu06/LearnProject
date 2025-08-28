#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc , const char *argv[] ){

    if(argc < 2){
        printf("argc not enough\n");
        return 1;
    }
    printf("%s进程 : %d启动\n",argv[1], getpid());

    return 0;
}