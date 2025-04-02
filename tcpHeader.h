// tcpHeader.h
#ifndef TCP_HEADER_H
#define TCP_HEADER_H

#include <stdint.h>

typedef unsigned char u_char;

int getTcpHeader(const u_char *packet, int start, int *src_port, int *dst_port);

#endif
