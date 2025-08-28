// 包含标准输入输出库、unistd库和标准库头文件
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 主函数：演示execve系统调用的使用
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc , const char *argv[]){

    // 定义进程名称
    char *name = "ribenguizi";
    
    // 打印当前进程信息
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


    // 定义要执行的程序参数和环境变量
    char *argvs[] = { "/home/du/dev/LearnProject/Process/test",name,NULL};
    char *envs[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", NULL};
    
    // 调用execve函数执行指定程序
    int ret = execve(argvs[0], argvs, envs);

    // 检查execve调用是否失败（如果成功则不会执行到这里）
    if(ret == -1){
        perror("execve error\n");
        return 1;
    }
}