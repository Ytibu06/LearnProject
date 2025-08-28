#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc , const char *argv[]){

    char *name = "ribenguizi";
    printf("我是%s 编号%d\n",name,getpid());

    /**
     * int execve (const char *__path, char *const __argv[], char *const __envp[])
     * 函数功能 : 用参数指定的程序替换当前进程。
     * 参数 :
     *  __path : 指定要执行的程序路径。
     *  __argv : 指定要执行的程序参数。
     *          参数__argv[0]为要执行的程序名，参数__argv[1]为第一个参数，最后一个参数为NULL，以此类推。
     *  __envp : 指定要执行的程序环境变量。
     *          环境变量参数：key=value, 最后一个参数为NULL。
     * return :
     *          失败返回-1
     */


    char *argvs[] = { "/home/du/dev/LearnProject/Process/test",name,NULL};
    char *envs[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", NULL};
    int ret = execve(argvs[0], argvs, envs);

    if(ret == -1){
        perror("execve error\n");
        return 1;
    }
}