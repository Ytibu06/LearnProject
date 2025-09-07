#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

//基于UDP协议的客户端程序


#define handle_error(cmd, result) \
    if (result < 0)               \
    {                             \
        perror(cmd);              \
        return -1;                \
    }

int main(int argc, char *argv[])
{
    int sockfd, binfd;
    char *buf = malloc(1024);

    //创建结构体，用于保存服务器端地址信息
    struct sockaddr_in server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t server_len = sizeof(server_addr);
    socklen_t client_len = sizeof(client_addr);

    // //UDP套接字编程流程
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    handle_error("socket", sockfd);
    // binfd = bind(sockfd, (struct sockaddr *)&server_addr, server_len);
    // handle_error("bind", binfd);
    do{
        printf("请输入数据：\n");
        int buf_len = read(STDIN_FILENO, buf, 1023);
        binfd = sendto(sockfd, buf, buf_len, 0, (struct sockaddr *)&server_addr, server_len);
        handle_error("sendto", binfd);
        memset(buf, 0, 1024);
        binfd = recvfrom(sockfd, buf, 1023, 0, NULL, NULL);
        handle_error("recvfrom", binfd);

        if(strncmp(buf, "EOF",3) != 0){
            printf("服务器%s %d返回数据：%s\n",
                inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port), buf);
        }
        
    }while (strncmp(buf, "EOF",3) != 0);
    free(buf);
    
    return 0;
}