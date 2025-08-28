#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, char const *argv[])
{
    char *name = "父进程";
    
    printf("%s %d继续运行...\n", name, getpid());

    __pid_t pid = fork();

    if(pid == -1){

        printf("创建子进程失败...\n");
        return 1;

    }else if(pid == 0){

        char*new_name = "系统调用";
        char *args[] = {"/home/du/dev/LearnProject/Process/test",new_name,NULL};
        char *envs[] = {NULL};

        int exR = execve(args[0], args, envs);

        if(exR == -1){
            printf("邀请新学员失败...\n");
            return 1;
        }
        
    }else{

        printf("%s %d创建子进程成功...\n", name, getpid());

        //阻塞父进程
        char by = fgetc(stdin);

    }

    return 0;
}