/*
 * @Author: ustc-mzw 2875226921@qq.com
 * @Date: 2022-11-05 14:09:55
 * @LastEditors: ustc-mzw 2875226921@qq.com
 * @LastEditTime: 2022-11-05 14:09:56
 * @FilePath: /cn_class/exp2/code/net.h
 * @Description: 
 * 
 * Copyright (c) 2022 by ustc-mzw 2875226921@qq.com, All Rights Reserved. 
 */
#pragma once

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TCP_SERVER_ADDRESS "127.0.0.1"
#define TCP_SERVER_PORT 8003
#define TCP_BUF_LENGTH 1000
#define CONNECTION_NUMBER 10

#define UDP_SERVER_ADDRESS "127.0.0.1"
#define UDP_SERVER_PORT 8002
#define UDP_BUF_LENGTH 1000

void perror_and_exit(const char *x) {
    perror(x);
    exit(1);
}

int Socket(int family, int type, int protocol) {
    int ret;
    if ((ret = socket(family, type, protocol)) < 0)
        perror_and_exit("socket error");
    return ret;
}

void Bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen) {
    if (bind(sockfd, my_addr, addrlen) < 0)
        perror_and_exit("bind error");
}

void Listen(int sockfd, int backlog) {
    if (listen(sockfd, backlog) < 0)
        perror_and_exit("listen error");
}

int Accept(int sockfd, struct sockaddr *client_addr, socklen_t *addrlen) {
    int ret;
    if ((ret = accept(sockfd, client_addr, addrlen)) < 0)
        perror_and_exit("accept error");
    return ret;
}

void Connect(int sockfd, const struct sockaddr *server_addr, socklen_t addrlen) {
    if (connect(sockfd, server_addr, addrlen) < 0)
        perror_and_exit("connect error");
}

ssize_t Recv(int sockfd, void *buf, size_t nbytes, int flags) {
    ssize_t n;
    if ((n = recv(sockfd, buf, nbytes, flags)) < 0)
        perror_and_exit("recv error");
    return n;
}

ssize_t Recvfrom(int sockfd, void *buf, size_t nbytes, int flags,
                 struct sockaddr *addr, socklen_t *addrlen) {
    ssize_t n;
    if ((n = recvfrom(sockfd, buf, nbytes, flags, addr, addrlen)) < 0)
        perror_and_exit("recvfrom error");
    return n;
}

void Send(int sockfd, const void *buf, size_t nbytes, int flags) {
    if (send(sockfd, buf, nbytes, flags) != (ssize_t)nbytes)
        perror_and_exit("send error");
}

void Sendto(int sockfd, const void *buf, size_t nbytes, int flags,
            const struct sockaddr *addr, socklen_t addrlen) {
    if (sendto(sockfd, buf, nbytes, flags, addr, addrlen) != (ssize_t)nbytes)
        perror_and_exit("sendto error");
}

void Shutdown(int sockfd, int how) {
    if (shutdown(sockfd, how) < 0)
        perror_and_exit("shutdown error");
}

void Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
    if (setsockopt(sockfd, level, optname, optval, optlen) < 0)
        perror_and_exit("setsockopt error");
}

int Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen) {
    int ret;
    if ((ret = getsockopt(sockfd, level, optname, optval, optlen)) < 0)
        perror_and_exit("getsockopt error");
    return ret;
}