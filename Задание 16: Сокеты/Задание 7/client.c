#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#define PAYLOAD "Hi!"
#define PAYLOAD_LEN 3

unsigned short checksum(unsigned short *buf, int nwords) {
    unsigned long sum = 0;
    for (; nwords > 0; nwords--)
        sum += *buf++;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

int main() {
    int sockfd;
    unsigned char buffer[1500];
    struct ethhdr *eth = (struct ethhdr *)buffer;
    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    struct udphdr *udp = (struct udphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));
    char *payload = (char *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr));
    struct sockaddr_ll serv;
    const char *interface = "enp0s8"; 
    const unsigned char src_mac[6] = {0x08,0x00,0x27,0x4a,0xd0,0x6e}; 
    const unsigned char dst_mac[6] = {0x74,0x56,0x3c,0x2c,0x76,0x96}; 

    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Ethernet Header
    memcpy(eth->h_dest, dst_mac, 6);
    memcpy(eth->h_source, src_mac, 6);
    eth->h_proto = htons(ETH_P_IP);

    // IP Header
    ip->ihl = 5;
    ip->version = 4;
    ip->tos = 0;
    ip->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + PAYLOAD_LEN);
    ip->id = htons(0x1234);
    ip->frag_off = 0;
    ip->ttl = 64;
    ip->protocol = IPPROTO_UDP;
    ip->check = 0;
    ip->saddr = inet_addr("192.168.1.107");  
    ip->daddr = inet_addr("192.168.1.105"); 
    ip->check = checksum((unsigned short *)ip, sizeof(struct iphdr)/2);

    // UDP Header
    udp->source = htons(12345);
    udp->dest = htons(54321);
    udp->len = htons(sizeof(struct udphdr) + PAYLOAD_LEN);
    udp->check = 0; 

    memcpy(payload, PAYLOAD, PAYLOAD_LEN);

    memset(&serv, 0, sizeof(serv));
    serv.sll_family = AF_PACKET;
    serv.sll_protocol = htons(ETH_P_IP);
    serv.sll_ifindex = if_nametoindex(interface);
    if (serv.sll_ifindex == 0) {
        perror("if_nametoindex");
        close(sockfd);
        exit(1);
    }
    serv.sll_halen = ETH_ALEN;
    memcpy(serv.sll_addr, dst_mac, 6);

    int frame_len = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr) + PAYLOAD_LEN;

    // Отправка
    if (sendto(sockfd, buffer, frame_len, 0, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("sendto");
        close(sockfd);
        exit(1);
    }


    // Прием пакета
    while (1) {
        unsigned char recv_buf[1500];
        ssize_t numbytes = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, NULL, NULL);
        if (numbytes < 0) {
            perror("recvfrom");
            close(sockfd);
            exit(1);
        }

        struct ethhdr *recv_eth = (struct ethhdr *)recv_buf;
        if (ntohs(recv_eth->h_proto) != ETH_P_IP) continue; // фильтр по EtherType

        struct iphdr *recv_ip = (struct iphdr *)(recv_buf + sizeof(struct ethhdr));
        if (recv_ip->protocol != IPPROTO_UDP) continue; // фильтр по протоколу IP

        struct udphdr *recv_udp = (struct udphdr *)((unsigned char *)recv_ip + recv_ip->ihl*4);

        if (ntohs(recv_udp->dest) != 12345) continue; 

        char *recv_payload = (char *)((unsigned char *)recv_udp + sizeof(struct udphdr));
        int recv_payload_len = ntohs(recv_udp->len) - sizeof(struct udphdr);

        printf("Received packet:\n");
        printf("From IP: %s\n", inet_ntoa(*(struct in_addr *)&recv_ip->saddr));
        printf("Payload: %.*s\n", recv_payload_len, recv_payload);
        break;
    }

    close(sockfd);
    return 0;
}
