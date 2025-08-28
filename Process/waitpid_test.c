// 包含unistd、标准输入输出、等待和系统类型头文件
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

// 主函数：演示waitpid函数的使用
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc, char const *argv[]){


    // 定义子进程状态变量
    int subProcess_status;
    
    // 打印当前进程ID
    printf("当前进程ID: %d\n",getpid());
    
    // 创建子进程
    pid_t pid = fork();

    // 检查fork是否失败
    if(pid < 0){
        perror("fork");
        return 1;

    }else if(pid == 0){

        // 子进程代码段
        // 定义要执行的程序参数和环境变量
        char *args[] = {"/usr/bin/ping","-c","20","www.baidu.com",NULL};
        char *envs[] = {NULL};

        // 打印子进程开始执行信息
        printf("子进程开始执行\n");

        // 在子进程中执行指定程序
        int exR = execve(args[0],args,envs);

        // 如果execve执行失败执行以下代码，如果成功程执行成功则不会执行以下代码
        if(exR < 0){

            perror("execve");
            return 1;
        }
    }else{

        // 父进程代码段
        // 打印父进程和子进程ID
        printf("父进程:%d  创建子进程:%d\n", getpid(), pid);

        // 等待子进程结束
        waitpid(pid,&subProcess_status,0);

    }

    // 打印进程结束信息
    printf("随着子进程结束，父进程也结束关闭\n");

    return 0;
}