#include "client.h"
#include "../common/protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/socket.h>

void run_client(const char *server_ip) {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockfd < 0) { 
	perror("socket"); 
	exit(1); 
    }
    int one = 1;
    setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one));

    struct sockaddr_in dest = {0};
    dest.sin_family = AF_INET;
    dest.sin_port = htons(SERVER_PORT);
    inet_aton(server_ip, &dest.sin_addr);

    char input[MAX_MSG_LEN];
    char packet[1500];

    while (1) {
        printf("Enter message (/exit to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/exit") == 0) {
            strcpy(input, CLOSE_MSG);
        }

        memset(packet, 0, sizeof(packet));
        struct iphdr *ip = (struct iphdr *)packet;
        struct udphdr *udp = (struct udphdr *)(packet + sizeof(struct iphdr));
        char *data = (char *)(udp + 1);

        int data_len = strlen(input);
        strcpy(data, input);

        ip->ihl = 5;
        ip->version = 4;
        ip->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + data_len);
        ip->protocol = IPPROTO_UDP;
        ip->saddr = INADDR_ANY;
        ip->daddr = dest.sin_addr.s_addr;
        ip->ttl = 64;

        udp->source = htons(CLIENT_PORT);
        udp->dest = htons(SERVER_PORT);
        udp->len = htons(sizeof(struct udphdr) + data_len);

        sendto(sockfd, packet, sizeof(struct iphdr) + sizeof(struct udphdr) + data_len,
               0, (struct sockaddr *)&dest, sizeof(dest));

        char buffer[1500];
        ssize_t n = recv(sockfd, buffer, sizeof(buffer), 0);
        if (n <= 0) continue;

        struct iphdr *rip = (struct iphdr *)buffer;
        struct udphdr *rup = (struct udphdr *)(buffer + rip->ihl * 4);
        char *recv_data = (char *)(rup + 1);
        int recv_len = ntohs(rup->len) - sizeof(struct udphdr);

        recv_data[recv_len] = '\0';
        printf("[Server]: %s\n", recv_data);

        if (strcmp(input, CLOSE_MSG) == 0) break;
    }

    close(sockfd);
}

