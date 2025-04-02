// ethernetHeader.c
#include "ethernetHeader.h"

void getHeader(const u_char *packet, const u_char **dst, const u_char **src) {
    // ether = packet[:12] #~14번째 byte 까지는 이더넷 헤더. type은 필요없으니 12까지만 취함.
    *dst = packet;
    *src = packet + 6;
}
