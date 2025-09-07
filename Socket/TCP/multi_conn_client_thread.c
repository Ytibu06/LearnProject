#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>


//建议一个多线程的网络连接客户端


//错误处理器
#define handle_error(cmd, result) if(result < 0) {perror(cmd);  return -1;}

void *read_from_server(void *argv)
{
    int sockfd = *(int *)argv;
    char *read_buf = NULL;
    ssize_t count = 0;

    read_buf = malloc(sizeof(char) * 1024);
    if (!read_buf)
    {
        perror("malloc client read_buf");
        return NULL;
    }

    while (count = recv(sockfd, read_buf, 1024, 0))
    {
        if (count < 0)
        {
            perror("recv");
        }
        fputs(read_buf, stdout);
    }

    printf("收到服务端的终止信号......\n");
    free(read_buf);

    return NULL;
}

void *write_to_server(void *argv)
{
    int sockfd = *(int *)argv;
    char *write_buf = NULL;
    ssize_t send_count;

    write_buf = malloc(sizeof(char) * 1024);

    if (!write_buf)
    {
        printf("写缓存分配失败，断开连接\n");
        shutdown(sockfd, SHUT_WR);
        perror("malloc client write_buf");

        return NULL;
    }

    while (fgets(write_buf, 1024, stdin) != NULL)
    {
        send_count = send(sockfd, write_buf, 1024, 0);
        if (send_count < 0)
        {
            perror("send");
        }
    }

    printf("接收到命令行的终止信号，不再写入，关闭连接......\n");
    shutdown(sockfd, SHUT_WR);
    free(write_buf);

    return NULL;
}

int main(int argc, char const *argv[])
{
    int sockfd, temp_result;
    pthread_t pid_read, pid_write;

    // 定义服务器地址结构体变量
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));   // 初始化结构体变量

    // 设置服务器地址结构体变量
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(6666);     // 连接端口 6666

    // 客户端网络编程流程
    sockfd = socket(AF_INET, SOCK_STREAM, 0);   // 创建套接字
    handle_error("socket", sockfd);
    //系统随机分配端口号
    temp_result = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));    // 连接服务器
    handle_error("connect", temp_result);

    //printf("成功连接服务器：%s %d\n",inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

    // 启动一个子线程，用来读取服务端数据，并打印到 stdout
    pthread_create(&pid_read, NULL, read_from_server, (void *)&sockfd);
    // 启动一个子线程，用来从命令行读取数据并发送到服务端
    pthread_create(&pid_write, NULL, write_to_server, (void *)&sockfd);

    // 阻塞主线程
    pthread_join(pid_read, NULL);
    pthread_join(pid_write, NULL);

    printf("关闭资源\n");
    close(sockfd);

    return 0;
}
