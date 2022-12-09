/*
 * @Author: ustc-mzw 2875226921@qq.com
 * @Date: 2022-11-05 09:40:23
 * @LastEditors: ustc-mzw 2875226921@qq.com
 * @LastEditTime: 2022-11-05 12:19:20
 * @FilePath: /cn_class/exp2/code/my_tcp_client.c
 * @Description: 
 * 
 * Copyright (c) 2022 by ustc-mzw 2875226921@qq.com, All Rights Reserved. 
 */
#include "net.h"

int main() {

    /* 建立套接字 */
    int sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* 建立tcp连接 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TCP_SERVER_PORT);
    if (inet_pton(AF_INET, TCP_SERVER_ADDRESS, &server_addr.sin_addr.s_addr) != 1) {
        perror_and_exit("inet_pton");
    }
    Connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    /* 发送数据 */
    while(1)
    {
        char msg[100] = {0};
        fgets(msg,100,stdin);
        msg[strlen(msg)-1] ='\0'; 
        if(strlen(msg) > 0)
        {
            Send(sockfd, msg, strlen(msg), 0);
            char buf[TCP_BUF_LENGTH] = {0};
            size_t pkt_len = Recv(sockfd, buf, TCP_BUF_LENGTH, 0);
            buf[strlen(buf)] = '\n';
            printf("%s",buf);
        }
        else break;
    }
    /* 关闭套接字 */
    close(sockfd);

    return 0;
}
