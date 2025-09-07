#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SOCKET_PATH "unix_domain.socket"
#define SERVER_MODE 1
#define CLIENT_MODE 2
#define BUF_LEN 1024

static struct sockaddr_un socket_addr;
static char *buf;

void handle_error(char *err_msg)    //错误处理函数
{
    perror(err_msg);
    unlink(SOCKET_PATH);
    exit(-1);
}

void server_mode(int sockfd)
{
    int client_fd, msg_len;
    struct sockaddr_un client_addr;
    int bind_fd = bind(sockfd, (struct sockaddr *)&socket_addr, sizeof(struct sockaddr_un)); //绑定socket
    if(bind_fd < 0){
        handle_error("bind");
    }

    int listen_fd = listen(sockfd, 128);
    if(listen_fd < 0){
        handle_error("listen");
    }

    int client_addr_len = sizeof(struct sockaddr_un);
    client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if(client_fd < 0){
        handle_error("accept");
    }
    printf("Accept client...\n");

    do{
        memset(buf, 0, BUF_LEN);
        msg_len = recv(client_fd, buf, BUF_LEN, 0);
        if(strncmp(buf,"EOF", 3) != 0){
            printf("Client: %s\n", buf);
            strcpy(buf, "ok\n\0");
        }else{
            printf("Client exit...\n");
        }
        send(client_fd, buf, strlen(buf), 0);
    }while (strncmp(buf,"EOF", 3) != 0);
    
}

void client_mode(int sockfd)
{
    int len,msg_len;
    len = connect(sockfd, (struct sockaddr *)&socket_addr, sizeof(struct sockaddr_un));
    if(len < 0){
        handle_error("connect");
    }
    printf("Connect to server...\n");
    do{
        printf("Please input message: \n");
        msg_len = read(STDIN_FILENO, buf, BUF_LEN);
        if(send(sockfd, buf, BUF_LEN, 0) < 0){
            handle_error("send");
        }
        memset(buf, 0, 1024);
        recv(sockfd, buf, 1024, 0);
        printf("Server: %s\n", buf);
    }while (strncmp(buf,"EOF", 3) != 0);
 
    if(shutdown(sockfd, SHUT_RDWR) < 0){
        handle_error("shutdown");
    }
    close(sockfd);
    free(buf);
}

int main(int argc, char *argv[])
{   //通过main方法传参的方式，启动不同的客户端和服务端

    int fd, mode = 0;
    if(argc == 1 || strncmp(argv[1], "server",6) == 0){
        mode = SERVER_MODE;
    }else if(strncmp(argv[1], "client",6) == 0){
        mode = CLIENT_MODE;
    }else{
        perror("Usage: ./socket_ipc [server|client]");
        exit(EXIT_FAILURE);
    }

    //创建socket
    memset(&socket_addr, 0, sizeof(struct sockaddr_un));
    buf = malloc(BUF_LEN);
    socket_addr.sun_family = AF_UNIX;
    strcpy(socket_addr.sun_path, SOCKET_PATH);
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(fd < 0){
        handle_error("socket");
    }


    switch (mode)
    {
    case SERVER_MODE :
        server_mode(fd);
        break;
    case CLIENT_MODE :
        client_mode(fd);
        break;
    default:
        break;
    }

    close(fd);
    free(buf);

    return 0;
}