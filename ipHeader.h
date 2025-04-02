// ipHeader.h
#ifndef IP_HEADER_H
#define IP_HEADER_H

#include <stdint.h>

typedef unsigned char u_char;

int getIpHeader(const u_char *packet, int start, char *src_ip, char *dst_ip);

#endif
