#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){

    int fd = open("io.txt", O_RDONLY);

    if(fd == -1){
        perror("open");
        _exit(EXIT_FAILURE);
    }

    char buffer[1024];  //数据存放
    ssize_t bytes_read;

    /**
     * ssize_t read (int __fd, void *__buf, size_t __nbytes)
     * 函数功能 : 
     *      从文件描述符fd中读取数据，并保存在buf中
     * 参数 :
     *        __fd : 文件描述符
     *        __buf : 存放数据的缓冲区
     *        __nbytes : 读取的字节数
     */
    while((bytes_read = read(fd, buffer, sizeof(buffer))) > 0){
        
        //文件描述符类的类型
        //stdin 标准输入 0
        //stdout 标准输出 1
        //stderr 标准错误 2
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    if(bytes_read == -1){
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    return 0;
}