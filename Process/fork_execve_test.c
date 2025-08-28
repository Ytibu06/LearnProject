#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, char const *argv[])
{
    char *name = "老学员";
    
    printf("%s %d继续在一层中运行...\n", name, getpid());

    __pid_t pid = fork();

    if(pid == -1){
        printf("邀请新学院失败...\n");
        return 1;
    }else if(pid == 0){
        char*new_name = "ergou";
        char *args[] = {"/home/du/dev/LearnProject/Process/test",new_name,NULL};
        char *envs[] = {NULL};
        int exR = execve(args[0], args, envs);
        if(exR == -1){
            printf("邀请新学员失败...\n");
            return 1;
        }
        
    }else{
        sleep(1);
        printf("%s %d邀请新学员成功...\n", name, getpid());
    }

    return 0;
}