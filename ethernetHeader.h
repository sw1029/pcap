// ethernetHeader.h
#ifndef ETHERNET_HEADER_H
#define ETHERNET_HEADER_H

typedef unsigned char u_char;

void getHeader(const u_char *packet, const u_char **dst, const u_char **src);

#endif
