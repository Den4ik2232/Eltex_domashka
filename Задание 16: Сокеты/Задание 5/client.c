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
    struct udphdr *udp_header;
    struct sockaddr_in serv;

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }
    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    const char *msg1 = "Hi!";
    int udp_len = sizeof(struct udphdr) + strlen(msg1);
    udp_header = (struct udphdr *)buf;
    udp_header->source = htons(11111);
    udp_header->dest = htons(12345);
    udp_header->len = htons(udp_len);
    udp_header->check = 0;
    memcpy(buf + sizeof(struct udphdr), msg1, strlen(msg1));

    if (sendto(fd, buf, udp_len, 0, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("sendto");
        close(fd);
        exit(1);
    }
    while (1) {
        unsigned char recvbuf[65536];
        struct sockaddr_in client;
        socklen_t addrlen = sizeof(client);
        ssize_t recvlen = recvfrom(fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&client, &addrlen);
        if (recvlen < 0) {
            perror("recvfrom");
            close(fd);
            exit(1);
        }
        struct iphdr *ip_header = (struct iphdr *)recvbuf;
        int ip_header_len = ip_header->ihl * 4;
        struct udphdr *udp = (struct udphdr *)(recvbuf + ip_header_len);
        char *payload = (char *)(recvbuf + ip_header_len + sizeof(struct udphdr));
        int payload_len = ntohs(udp->len) - sizeof(struct udphdr);
        if (ntohs(udp->source) == 12345 && ntohs(udp->dest) == 11111) {
            printf("Received from server: %.*s\n", payload_len, payload);
            break;
        }
    }

    const char *msg2 = "close";
    memset(buf, 0, sizeof(buf));
    udp_len = sizeof(struct udphdr) + strlen(msg2);
    udp_header = (struct udphdr *)buf;
    udp_header->source = htons(11111);
    udp_header->dest = htons(12345);
    udp_header->len = htons(udp_len);
    udp_header->check = 0;
    memcpy(buf + sizeof(struct udphdr), msg2, strlen(msg2));

    if (sendto(fd, buf, udp_len, 0, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("sendto close");
    } 
    close(fd);
    return 0;
}
