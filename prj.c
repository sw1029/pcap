// prj.c
// 코드 리뷰 시에 기능별로 분리하여 코드를 짜는 것이 
// 가시성이 더 나을 것 같아 분리하여 작성합니다.

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>

#include "ethernetHeader.h"
#include "ipHeader.h"
#include "tcpHeader.h"
#include "message.h"

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;
    pcap_if_t *device;
    pcap_t *cap;
    struct pcap_pkthdr *header;
    const u_char *packet;

    // device = pcapy.findalldevs()[0] #eth0 사용
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "장치를 찾을 수 없습니다: %s\n", errbuf);
        return 1;
    }
    device = alldevs;

    // cap = pcapy.open_live(device, 65536, 1, 100)
    cap = pcap_open_live(device->name, 65536, 1, 100, errbuf);
    if (cap == NULL) {
        fprintf(stderr, "장치를 열 수 없습니다: %s\n", errbuf);
        return 1;
    }

    // cap.setfilter('tcp')
    struct bpf_program fp;
    if (pcap_compile(cap, &fp, "tcp", 0, PCAP_NETMASK_UNKNOWN) == -1 ||
        pcap_setfilter(cap, &fp) == -1) {
        fprintf(stderr, "필터 적용 실패: %s\n", pcap_geterr(cap));
        return 1;
    }

    // _ , packet = cap.next() #패킷이 들어올 때 까지 무한 대기
    int res = pcap_next_ex(cap, &header, &packet);
    if (res <= 0) {
        printf("패킷 수신 실패\n");
        return 1;
    }

    const u_char *dst_mac, *src_mac;
    getHeader(packet, &dst_mac, &src_mac);

    char src_ip[INET_ADDRSTRLEN], dst_ip[INET_ADDRSTRLEN];
    int tcp_idx = getIpHeader(packet, 14, src_ip, dst_ip);

    int src_port, dst_port;
    int msg_idx = getTcpHeader(packet, tcp_idx, &src_port, &dst_port);

    const u_char *msg = getMsg(packet, msg_idx);

    printf("src_mac = %02x%02x%02x%02x%02x%02x\n",
           src_mac[0], src_mac[1], src_mac[2],
           src_mac[3], src_mac[4], src_mac[5]);

    printf("dst_mac = %02x%02x%02x%02x%02x%02x\n",
           dst_mac[0], dst_mac[1], dst_mac[2],
           dst_mac[3], dst_mac[4], dst_mac[5]);

    printf("src_ip = %s\n", src_ip);
    printf("dst_ip = %s\n", dst_ip);

    printf("src_port = %d\n", src_port);
    printf("dst_port = %d\n", dst_port);

    printf("msg = %.*s\n", (int)(header->caplen - msg_idx), msg);

    pcap_close(cap);
    pcap_freealldevs(alldevs);

    return 0;
}
