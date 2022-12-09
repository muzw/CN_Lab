/*
 * @Author: ustc-mzw 2875226921@qq.com
 * @Date: 2022-11-05 12:42:55
 * @LastEditors: ustc-mzw 2875226921@qq.com
 * @LastEditTime: 2022-11-05 13:09:01
 * @FilePath: /cn_class/exp2/code/my_udp_server.c
 * @Description: 
 * 
 * Copyright (c) 2022 by ustc-mzw 2875226921@qq.com, All Rights Reserved. 
 */
#include "net.h"

int main() {

    /* 建立套接字 */
    int sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int enable = 1;
    Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    /* 绑定端口 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(UDP_SERVER_PORT);
    if (inet_pton(AF_INET, UDP_SERVER_ADDRESS, &server_addr.sin_addr.s_addr) != 1) {
        perror_and_exit("inet_pton");
    }

    Bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    /* 接收数据 */
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    char buf[UDP_BUF_LENGTH];
    for(int i = 0; i < 10; i++)
    {
        size_t pkt_len = Recvfrom(sockfd, buf, UDP_BUF_LENGTH, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        buf[pkt_len] = '\0';
        char addr[100];
        printf("Received from:%s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("Message received: %s[%zu bytes]\n", buf, pkt_len);
    }



    /* 关闭套接字 */
    close(sockfd);

    return 0;
}
