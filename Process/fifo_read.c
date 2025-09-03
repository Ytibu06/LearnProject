#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


//有名管道：mkfifo
/**
 * int mkfifo (const char *__path, __mode_t __mode)
 * 函数功能：创建一个管道
 * 函数参数：
 *          __path:管道路径
 *          __mode:管道权限
 * return : 成功返回0，失败返回-1
 */


int main(int argc, char *argv[]){

    int fd;
    char *pipe_path = "/tmp/myfifo";
    int fifoR = mkfifo(pipe_path, 0664);
    //管道创建失败
    if(fifoR < 0){
        // 如果FIFO已经存在，忽略这个错误
        if(errno != EEXIST) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    //对有名管道的特殊文件创建fd
    fd = open(pipe_path, O_RDONLY);

    //打开管道错误，进行错误输出
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[1024];
    ssize_t read_num;

    //读取管道中数据并输出数据到控制台中
    while ((read_num = read(fd, buf, sizeof(buf))) > 0){
        write(STDOUT_FILENO, buf, read_num);
    }

    //读取数据失败
    if(read_num < 0){
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("读取管道数据完成，进程终止\n");
    close(fd);

    return 0;
}