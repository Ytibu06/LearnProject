#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>


//建立一个多线程网络连接服务器

//错误处理器
#define handle_error(cmd, result) if(result < 0) {perror(cmd);  return -1;}


void *read_from_client_then_write(void *argv)
{   //读取数据进行恢复
    int client_fd = *(int *)argv;

    char *read_buf = NULL, *write_buf = NULL;
    ssize_t count = 0, send_count = 0;

    read_buf = malloc(sizeof(char ) * 1024);
    write_buf = malloc(sizeof(char ) * 1024);
    if(!read_buf)
    {
        perror("read_buf malloc");
        close(client_fd);
        return NULL;
    }
    if(!write_buf){
        perror("write_buf malloc");
        close(client_fd);
        return NULL;
    }

    while(count = recv(client_fd, read_buf, 1024, 0)){
        if(count < 0){
            perror("recv");
        }
        printf("收到来自 %d 的数据：%s\n", client_fd,read_buf);
        strcpy(write_buf, "reveived~\n");
        send_count = send(client_fd, write_buf, 1024, 0);
        if(send_count < 0){
            perror("send");
        }

    }
    shutdown(client_fd, SHUT_RDWR);     //关闭读写
    close(client_fd);
    free(read_buf);
    free(write_buf);
    
    return NULL;
}


int main(int argc, char *argv[])
{

    int sock_fd, bind_fd, listen_fd;
    struct sockaddr_in server_addr, client_addr;    // 服务器地址结构体

    memset(&server_addr, 0, sizeof(server_addr));   //初始化地址结构体
    memset(&client_addr, 0, sizeof(client_addr));

    //设置服务器地址结构体
    server_addr.sin_family = AF_INET;   //设置协议族
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    //设置IP地址
    server_addr.sin_port = htons(6666); //设置端口号

    //socket编程流程：socket -> bind -> listen -> accept -> read -> write -> close
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);    //创建套接字
    handle_error("socket", sock_fd);
    bind_fd = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));    //绑定套接字
    handle_error("bind", bind_fd);
    listen_fd = listen(sock_fd, 128);   //监听套接字
    handle_error("listen", listen_fd);

    //接受多个客户端连接
    socklen_t client_addr_len = sizeof(client_addr);
    while (1)
    {
        //创建多个线程，处理多个客户端请求
        pthread_t  pid_read_write;
        int client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        handle_error("accept", client_fd);
        printf("与客户端 %s %d 建立连接 %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), client_fd);
        //创建一个线程，处理多个客户端请求 
        int pth_cre_result = pthread_create(&pid_read_write, NULL, read_from_client_then_write, (void *)&client_fd);
        if(pth_cre_result ){
            perror("pthread_create");
        }
        pthread_detach(pid_read_write);
    }

    close(sock_fd);
    printf("服务器已退出\n");

    return 0;
}
