#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

// 关于缓冲区

int is_buffer(FILE *file) {
    if (setvbuf(file, NULL, _IONBF, 0) != 0) {
        perror("Failed to set buffer mode");
        return 1;
    }
    fprintf(file, "hello"); 
}
int all_buffer(FILE *file){
    fprintf(file, "hello");
    fflush(file);
}

int line_buffer(FILE *file) {
    if (setvbuf(file, NULL, _IOLBF, 0) != 0) {
        perror("Failed to set buffer mode");
        return 1;
    }
    fprintf(file, "hello\n");
}
int main() {
    
    FILE *file = fopen("/home/du/dev/LearnProject/Socket/TCP/test.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    //设置文件为无缓冲模式
    //is_buffer(file);

    //设置文件为全缓冲模式，手动刷新缓冲区
    //all_buffer(file);

    //设置文件为行缓冲模式,遇到换行符刷新缓冲区
    line_buffer(file);
       

    char *argv[] = {"/usr/bin/ping", "-c", "1", "www.baidu.com", NULL};
    char *envp[] = {NULL};

    execve("/usr/bin/ping", argv, envp);
    perror("execve");

    return 0;
}