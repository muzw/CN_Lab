/*
 * @Author: ustc-mzw 2875226921@qq.com
 * @Date: 2022-11-11 10:19:23
 * @LastEditors: ustc-mzw 2875226921@qq.com
 * @LastEditTime: 2022-11-11 10:35:48
 * @FilePath: /code/1.stop-and-wait/rdt_stopwait_receiver.c
 * @Description: 
 * 
 * Copyright (c) 2022 by ustc-mzw 2875226921@qq.com, All Rights Reserved. 
 */
#include "net.h"

/**
 * 接收端接收函数
 * @param save_file_name - 保存文件名
 * @param sockfd - 接收数据的socket
 */
int receive_file(char *save_file_name, int sockfd) {
    // 将收到的RDT数据包按顺序写到此文件中
    FILE *fp;
    if ((fp = fopen(save_file_name, "w")) == NULL) {
        printf("open file : %s failed.\n", save_file_name);
        return 1;
    }

    // 总共接收的字节数
    int total_recv_byte = 0;

    // 当前接收端需要的数据包序列号
    int exp_seq_num = RDT_BEGIN_SEQ;

    //接收RDT数据包，直到所有数据全部接收完毕
    while (1) {
        // step 1. 接收RDT数据包
        char rdt_pkt[RDT_PKT_MAX_LEN];
        int pkt_len = recv(sockfd,rdt_pkt,RDT_PKT_MAX_LEN,0);

        // step 2. 解封装RDT数据包
        char rdt_data[RDT_DATA_MAX_LEN];
        int seq_num, flag;
        int data_len = unpack_rdt_pkt(rdt_data,rdt_pkt,pkt_len,&seq_num,&flag);

        // step 3. 检查此数据包是否为期待的数据包 : seq_num==exp_seq_num
        // 写入文件请使用fwrite()函数，例如： fwrite(rdt_data, sizeof(char), data_len, fp);
        /* TODO */
        printf("seqnum:%d\n",seq_num);
        if(seq_num == exp_seq_num)
        {
            fwrite(rdt_data, sizeof(char), data_len, fp);
            exp_seq_num += 1;
            total_recv_byte += data_len;


        }
            // step 4. 封装一个新的RDT数据包(ACK包)
            char reply_rdt_pkt[RDT_PKT_MAX_LEN];
            char* ask_data;
            int reply_pkt_len = pack_rdt_pkt(ask_data,reply_rdt_pkt,0,seq_num,RDT_CTRL_ACK);

            // step 5. 调用不可靠数据传输发送新的RDT数据包(ACK包)
            udt_send(sockfd,reply_rdt_pkt,reply_pkt_len,0);
        if (flag == RDT_CTRL_END) {
            break;
        }
    }

    printf("\n\n");
    printf("Receive finished. Write to file %s.\n", save_file_name);
    printf("Total recv %d byte\n", total_recv_byte);

    fflush(fp);
    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("wrong argument!\n");
        printf("usage: %s save_file\n", argv[0]);
        exit(0);
    }

    int sockfd = init_socket_receiver();
    if (receive_file(argv[1], sockfd) != 0) {
        printf("receive file %s failed.\n", argv[1]);
        close(sockfd);
        exit(1);
    }

    close(sockfd);
    return 0;
}
