#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//fork()函数：创建一个子进程


int main(int argc, char const *argv[]){

    //调用fork之前，代码运行在父进程中
    printf("本进程id : %d\n",getpid());

    //使用fork创建子进程
    /**
     * __pid_t fork (void) __THROWNL;
     * return -1 : 报错
     *         0 : 父进程中表示子进程的PID
     *         3 : 子进程中显示为0
     */

    //fork之后，所有代码都是父子进程各自执行一次
    pid_t pid = fork();

    //printf("this process id is %d\n", pid);

    if(pid<0){
        printf("新进程加入失败\n");
        return 1;
    }else if (pid == 0){
        //执行单独的子进程代码
        printf("进程：%d加入成功，为进程：%d的子进程\n",getpid(),getppid());
    }else{
        //执行单独父进程代码
        printf("父进程%d继续执行，构建出子进程%d\n",getpid(),pid);
    }
    

    return 0;
}