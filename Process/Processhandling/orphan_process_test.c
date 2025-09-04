// 包含标准输入输出库、unistd库、标准库和系统类型头文件
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

//孤儿进程：父进程退出，子进程成为孤儿进程，被init进程收养
/**
 * 避免父进程退出，子进程成为孤儿进程，从而避免
 */

// 主函数：演示孤儿进程的产生
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc, char const *argv[])
{
    // 定义父进程名称
    char *name = "父进程";
    
    // 打印父进程信息
    printf("%s %d继续运行...\n", name, getpid());

    // 创建子进程
    __pid_t pid = fork();

    // 检查fork是否失败
    if(pid == -1){

        printf("创建子进程失败...\n");
        return 1;

    }else if(pid == 0){

        // 子进程代码段
        // 定义新进程名称
        char*new_name = "系统调用";
        
        // 定义要执行的程序参数和环境变量
        char *args[] = {"/home/du/dev/LearnProject/Process/block_test",new_name,NULL};
        char *envs[] = {NULL};

        // 在子进程中执行指定程序
        int exR = execve(args[0], args, envs);

        // 检查execve是否失败
        if(exR == -1){
            printf("邀请新学员失败...\n");
            return 1;
        }
        
    }else{

        // 父进程代码段
        // 打印父进程信息
        printf("%s %d创建子进程成功...\n", name, getpid());

    }

    return 0;
}