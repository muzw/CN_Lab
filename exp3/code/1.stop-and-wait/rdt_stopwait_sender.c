#include "net.h"

/**
 * 发送文件
 * @param send_file_name - 待发送的文件名
 * @param sockfd - 发送数据的socket
 */
int deliver_file(char *send_file_name, int sockfd) {
    // 从此文件读取数据，包装成RDT数据包
    FILE *fp;
    if ((fp = fopen(send_file_name, "r")) == NULL) {
        printf("open file : %s failed.\n", send_file_name);
        return 1;
    }

    // 总共发送的字节数
    int total_send_byte = 0;

    // 当前发送端需要发送的数据包序列号
    int seq_num = RDT_BEGIN_SEQ;

    // 发送RDT数据包，直到文件结束
    int counter = 1;
    while (1) {
        char rdt_data[RDT_DATA_MAX_LEN];
        int data_len = fread(rdt_data, sizeof(char), RDT_DATA_MAX_LEN, fp);

        // 如果已经读到发送文件的结尾，设置数据包类型为RDT_CTRL_END
        // 否则设置数据包类型为RDT_CTRL_DATA
        int flag = (data_len == 0) ? RDT_CTRL_END : RDT_CTRL_DATA;

        // step 1. 封装RDT数据包
        char rdt_pkt[RDT_PKT_MAX_LEN];
        int pkt_len = pack_rdt_pkt(rdt_data,rdt_pkt,data_len,seq_num,flag);

        // step 2. 发送RDT数据包，重传直到收到ACK
        while (1) {
            // step 2-1. 调用不可靠数据传输发送新的RDT数据包
            printf("[Sender]Packet #%d: %d bytes. Send count #%d\n", seq_num, pkt_len, counter++);
            udt_send(sockfd,rdt_pkt,pkt_len,0);

            // step 2-2. 一直等待到文件描述符集合中某个文件有可读数据，或者到达超时时限： poll()
            struct pollfd pollfd = {sockfd, POLLIN};
            /* TODO */
            int poll_ret = poll(&pollfd,1,RDT_TIME_OUT);
            printf("poll_ret:%d\n",poll_ret);
            if(poll_ret > 0)
            {
                char rdt_pkt_ASK[RDT_HEADER_LEN];
                recv(sockfd,rdt_pkt_ASK,RDT_HEADER_LEN,0);

                char data_buf[RDT_PKT_MAX_LEN];
                int pkt_len;
                 int reply_seq_num;
                  int flag;

                unpack_rdt_pkt(data_buf,rdt_pkt_ASK,RDT_HEADER_LEN,&reply_seq_num,&flag);
                if (flag == RDT_CTRL_ACK && reply_seq_num == seq_num) break;
                else
                {
                    printf("重发\n");
                    continue;
                }

            } 
            else
            { 
                printf("重发\n");
                continue;
            }
        }

        // step 3. 发送成功，更新seq_num和total_send_byte
        /* TODO */
        seq_num += 1;
        total_send_byte += data_len;

        if (flag == RDT_CTRL_END) {
            break;
        }
    }

    printf("\n\n");
    printf("Send file %s finished.\n", send_file_name);
    printf("Total send %5d bytes.\n", total_send_byte);

    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("wrong argument!\n");
        printf("usage: %s send_file_name. \n", argv[0]);
        exit(0);
    }

    int sockfd = init_socket_sender();
    if (deliver_file(argv[1], sockfd) != 0) {
        printf("deliver file %s failed.\n", argv[1]);
        close(sockfd);
        exit(1);
    }

    close(sockfd);
    return 0;
}
