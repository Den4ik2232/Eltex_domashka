#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <errno.h>


int main() {
    int fd;
    unsigned char buf[65536] = {0};
    struct iphdr *ip_header;
    struct udphdr *udp_header;
    struct sockaddr_in serv;

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int flag = 1;
    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag)) < 0) {
        perror("setsockopt");
        close(fd);
        exit(EXIT_FAILURE);
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    const char *msg1 = "Hi!";
    int payload_len = strlen(msg1);
    int udp_len = sizeof(struct udphdr) + payload_len;
    int ip_len = sizeof(struct iphdr) + udp_len;

    ip_header = (struct iphdr *)buf;
    ip_header->ihl = 5;
    ip_header->version = 4;
    ip_header->tos = 0;
    ip_header->tot_len = htons(ip_len);
    ip_header->frag_off = 0;
    ip_header->ttl = 64;
    ip_header->protocol = IPPROTO_UDP;
    ip_header->daddr = serv.sin_addr.s_addr;

    udp_header = (struct udphdr *)(buf + sizeof(struct iphdr));
    udp_header->source = htons(11111);
    udp_header->dest = htons(12345);
    udp_header->len = htons(udp_len);
    udp_header->check = 0; 

    memcpy(buf + sizeof(struct iphdr) + sizeof(struct udphdr), msg1, payload_len);

    if (sendto(fd, buf, ip_len, 0, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("sendto");
        close(fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        unsigned char recvbuf[65536];
        struct sockaddr_in client;
        socklen_t addrlen = sizeof(client);
        ssize_t recvlen = recvfrom(fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&client, &addrlen);
        if (recvlen < 0) {
            perror("recvfrom");
            close(fd);
            exit(EXIT_FAILURE);
        }
        struct iphdr *recv_ip = (struct iphdr *)recvbuf;
        int ip_header_len = recv_ip->ihl * 4;
        struct udphdr *recv_udp = (struct udphdr *)(recvbuf + ip_header_len);
        char *payload = (char *)(recvbuf + ip_header_len + sizeof(struct udphdr));
        int pl_len = ntohs(recv_udp->len) - sizeof(struct udphdr);
        if (ntohs(recv_udp->source) == 12345 && ntohs(recv_udp->dest) == 11111) {
            printf("Received from server: %.*s\n", pl_len, payload);
            break;
        }
    }

    const char *msg2 = "close";
    memset(buf, 0, sizeof(buf));
    payload_len = strlen(msg2);
    udp_len = sizeof(struct udphdr) + payload_len;
    ip_len = sizeof(struct iphdr) + udp_len;

    ip_header = (struct iphdr *)buf;
    ip_header->ihl = 5;
    ip_header->version = 4;
    ip_header->tos = 0;
    ip_header->tot_len = htons(ip_len);
    ip_header->frag_off = 0;
    ip_header->ttl = 64;
    ip_header->protocol = IPPROTO_UDP;
    ip_header->daddr = serv.sin_addr.s_addr;

    udp_header = (struct udphdr *)(buf + sizeof(struct iphdr));
    udp_header->source = htons(11111);
    udp_header->dest = htons(12345);
    udp_header->len = htons(udp_len);
    udp_header->check = 0;

    memcpy(buf + sizeof(struct iphdr) + sizeof(struct udphdr), msg2, payload_len);

    if (sendto(fd, buf, ip_len, 0, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("sendto close");
    }

    close(fd);
    return 0;
}
