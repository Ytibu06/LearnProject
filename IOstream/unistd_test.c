#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main() {

    /**
     * int open (const char *__path, int __oflag, ...)
     * 函数功能 ：打开文件
     * 参数 ：
     *      __path: 文件路径
     *      __oflag: 文件打开方式
     *              O_RDONLY: 只读
     *              O_WRONLY: 只写
     *              O_RDWR: 读写
     *              O_CREAT: 如果文件不存在，则创建
     *              O_TRUNC: 如果文件存在，则截断
     *              O_APPEND: 如果文件存在，则追加
     *       ...: 如果__oflag为O_CREAT或O_TMPFILE，则必须提供此参数，表示文件权限
     * return : 成功返回文件描述符，失败返回-1
     */
    int fd = open("io.txt", O_RDONLY | O_CREAT, 0664);
    if (fd == -1) {
        printf("文件打开失败\n");
    }


  return 0;
}