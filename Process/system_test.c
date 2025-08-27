#include <stdio.h>
#include <stdlib.h>

int main(void){


    /**
     * int system (const char *__command) __wur;
     * const char *_command : 使用Linux命令创建一个子进程
     * return : 成功返回0 失败返回失败编号
     */
    int sysR = system("ping -c 10  www.atguigu.com");

    if(sysR != 0){
        perror("system");
        exit(EXIT_FAILURE);
    }

    return 0;
}