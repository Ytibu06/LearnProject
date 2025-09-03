#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>  // 添加此头文件，这是mkfifo所需的
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// 程序功能：演示有名管道(FIFO)的使用
// 有名管道是一种进程间通信(IPC)机制，允许无关联的进程之间进行通信
// 与无名管道不同，有名管道有文件名，可以在不相关的进程间使用

// mkfifo函数用于创建有名管道
/**
 * int mkfifo (const char *__path, __mode_t __mode)
 * 函数功能：创建一个有名管道(First In First Out)
 * 函数参数：
 *          __path:管道文件路径，创建后的管道以文件形式存在于文件系统中
 *          __mode:管道文件的访问权限，如0664表示用户可读写，组用户和其他用户只读
 * 返回值：成功返回0，失败返回-1，并设置errno
 */


int main(int argc, char *argv[]){
    // 文件描述符，用于后续的文件操作
    int fd;
    
    // 定义管道文件路径
    char *pipe_path = "/tmp/myfifo";
    
    // 创建有名管道
    int fifoR = mkfifo(pipe_path, 0664);

    // 检查mkfifo函数是否执行成功
    if(fifoR != 0){
        // 如果FIFO已经存在，忽略这个错误
        if(errno != EEXIST) {
            // perror会打印错误信息，帮助调试
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    // 以只读方式打开管道文件
    fd = open(pipe_path, O_WRONLY);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 定义缓冲区用于存储读取的数据
    char buf[1024];
    
    // 存储实际读取的字节数
    ssize_t read_num;

    // 从标准输入(STDIN_FILENO，即键盘)读取数据到缓冲区
    // 当读取到数据时循环处理
    while ((read_num = read(STDIN_FILENO, buf, sizeof(buf))) > 0){
        //将读取的数据写入管道
        write(fd, buf, read_num);
    }

    //读取控制台数据失败，进行错误输出，关闭文件，退出程序
    if(read_num < 0){
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    //数据写入管道符完毕，进行提示，关闭文件
    printf("创建管道数据完成，进程终止\n");
    close(fd);

    //释放管道，清楚对应的特殊文件
    if(unlink(pipe_path) == -1){
        perror("unlink");
    }

    return 0;
}