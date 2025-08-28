#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[]){


    int subProcess_status;
    printf("当前进程ID: %d\n",getpid());
    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        return 1;

    }else if(pid == 0){

        char *args[] = {"/usr/bin/ping","-c","20","www.baidu.com",NULL};
        char *envs[] = {NULL};

        printf("子进程开始执行\n");

        int exR = execve(args[0],args,envs);

        // 如果execve执行失败执行以下代码，如果成功程执行成功则不会执行以下代码
        if(exR < 0){

            perror("execve");
            return 1;
        }
    }else{

        printf("父进程:%d  创建子进程:%d\n", getpid(), pid);

        // 等待子进程结束
        waitpid(pid,&subProcess_status,0);

    }

    printf("随着子进程结束，父进程也结束关闭\n");

    return 0;
}