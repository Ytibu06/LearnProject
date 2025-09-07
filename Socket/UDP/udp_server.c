#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

//基于UDP协议的服务器端程序


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

    //UDP套接字编程流程
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    handle_error("socket", sockfd);
    binfd = bind(sockfd, (struct sockaddr *)&server_addr, server_len);
    handle_error("bind", binfd);
    do{
        memset(buf, 0, sizeof(buf));
        binfd = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_len);
        handle_error("recvfrom", binfd);
        if(strncmp(buf, "EOF",3) != 0){
            printf("接收到 client ip: %s, port: %d 的信息为 %s:\n", 
                inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);
            strcpy(buf, "I have received your message.");
        }else{
            printf("client ip: %s, port: %d 退出了.\n", 
                inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        }
        binfd = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&client_addr, client_len);
        handle_error("sendto", binfd);
    }while (strncmp(buf, "EOF",3) != 0);

    free(buf);
    return 0;
}