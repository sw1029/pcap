// message.c
#include "message.h"

const u_char *getMsg(const u_char *packet, int start) {
    return packet + start;
}
