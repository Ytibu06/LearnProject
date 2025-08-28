#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
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

    if(fifoR < 0){
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    //
    fd = open(pipe_path, O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[1024];
    ssize_t read_num;
    read_num = read(STDIN_FILENO, buf, sizeof(buf));
    while (read_num > 0){

        write(fd, buf, read_num);
    }
    if(read_num < 0){
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("read %ld bytes from fifo\n", read_num);
    


    return 0;
}