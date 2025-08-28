// 包含标准输入输出库和标准库头文件
#include <stdio.h>
#include <stdlib.h>

// 主函数：演示system函数的使用
int main(void){


    /**
     * int system (const char *__command) __wur;
     * const char *_command : 使用Linux命令创建一个子进程
     * return : 成功返回0 失败返回失败编号
     */
     
    // 使用system函数执行ping命令
    int sysR = system("ping -c 10  www.atguigu.com");

    // 检查system调用是否失败
    if(sysR != 0){
        perror("system");
        exit(EXIT_FAILURE);
    }

    return 0;
}