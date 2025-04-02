// tcpHeader.c
#include <string.h>
#include <arpa/inet.h>
#include "tcpHeader.h"

int getTcpHeader(const u_char *packet, int start, int *src_port, int *dst_port) {
    const u_char *tcp = packet + start;

    uint16_t src, dst;
    uint8_t offset;

    memcpy(&src, tcp, 2);
    memcpy(&dst, tcp + 2, 2);
    memcpy(&offset, tcp + 12, 1);

    *src_port = ntohs(src);
    *dst_port = ntohs(dst);

    int tcp_len = (offset >> 4) * 4;

    return start + tcp_len;
}
