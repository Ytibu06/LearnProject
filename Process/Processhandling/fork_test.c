// 包含标准输入输出库、系统类型和unistd头文件
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//fork()函数：创建一个子进程


// 主函数：演示fork系统调用的使用
// 参数argc：命令行参数个数
// 参数argv：命令行参数数组
int main(int argc, char const *argv[]){

    //调用fork之前，代码运行在父进程中
    // 打印当前进程ID
    printf("本进程id : %d\n",getpid());

    //使用fork创建子进程
    /**
     * __pid_t fork (void) __THROWNL;
     * return -1 : 报错
     *         0 : 父进程中表示子进程的PID
     *         3 : 子进程中显示为0
     */

    //fork之后，所有代码都是父子进程各自执行一次
    // 调用fork创建子进程
    pid_t pid = fork();

    //printf("this process id is %d\n", pid);

    // 检查fork是否失败
    if(pid<0){
        printf("新进程加入失败\n");
        return 1;
    }else if (pid == 0){
        // 子进程代码段
        // 执行单独的子进程代码
        printf("进程：%d加入成功，为进程：%d的子进程\n",getpid(),getppid());
    }else{
        // 父进程代码段
        // 执行单独父进程代码
        printf("父进程%d继续执行，构建出子进程%d\n",getpid(),pid);
    }
    

    return 0;
}