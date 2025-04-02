// ipHeader.c
#include <string.h>
#include <arpa/inet.h>
#include "ipHeader.h"

int getIpHeader(const u_char *packet, int start, char *src_ip, char *dst_ip) {
    // start_byte = packet[start] #길이를 구하기 위한 첫 번째 바이트
    uint8_t start_byte = packet[start];

    // ip_len = (start_byte % 16) * 4
    int ip_len = (start_byte & 0x0F) * 4;

    const u_char *ip = packet + start;

    struct in_addr src_raw, dst_raw;
    memcpy(&src_raw, ip + 12, 4);
    memcpy(&dst_raw, ip + 16, 4);

    strcpy(src_ip, inet_ntoa(src_raw));
    strcpy(dst_ip, inet_ntoa(dst_raw));

    return start + ip_len;
}
