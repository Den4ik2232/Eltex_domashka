#include "server.h"
#include "../common/protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/socket.h>

struct client_entry {
    struct in_addr ip;
    uint16_t port;
    int msg_count;
};

struct client_entry clients[MAX_CLIENTS];
int client_count = 0;

int find_or_add_client(struct in_addr ip, uint16_t port) {
    for (int i = 0; i < client_count; ++i) {
        if (clients[i].ip.s_addr == ip.s_addr && clients[i].port == port)
            return i;
    }
    if (client_count < MAX_CLIENTS) {
        clients[client_count].ip = ip;
        clients[client_count].port = port;
        clients[client_count].msg_count = 0;
        return client_count++;
    }
    return -1;
}

void remove_client(struct in_addr ip, uint16_t port) {
    for (int i = 0; i < client_count; ++i) {
        if (clients[i].ip.s_addr == ip.s_addr && clients[i].port == port) {
            clients[i] = clients[--client_count];
            return;
        }
    }
}

void run_server() {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockfd < 0) { perror("socket"); exit(1); }

    char buffer[65536];
    struct sockaddr_in src_addr;
    socklen_t addrlen = sizeof(src_addr);

    printf("Server start, port = %d\n", SERVER_PORT);

    while (1) {
        ssize_t len = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                               (struct sockaddr *)&src_addr, &addrlen);
        if (len < 0) continue;

        struct iphdr *ip = (struct iphdr *)buffer;
        if (ip->protocol != IPPROTO_UDP) continue;

        struct udphdr *udp = (struct udphdr *)(buffer + (ip->ihl * 4));
        char *payload = (char *)(udp + 1);
        int payload_len = ntohs(udp->len) - sizeof(struct udphdr);
        payload[payload_len] = '\0';

        uint16_t src_port = ntohs(udp->source);
        uint16_t dst_port = ntohs(udp->dest);

        if (dst_port != SERVER_PORT) continue;

        if (strcmp(payload, CLOSE_MSG) == 0) {
            remove_client(*(struct in_addr *)&ip->saddr, src_port);
            printf("Client disconnect: %s:%d\n", inet_ntoa(*(struct in_addr *)&ip->saddr), src_port);
            continue;
        }

        int id = find_or_add_client(*(struct in_addr *)&ip->saddr, src_port);
        if (id < 0) continue;
        clients[id].msg_count++;

        char reply[MAX_MSG_LEN];
        snprintf(reply, sizeof(reply), "%s %d", payload, clients[id].msg_count);

        char packet[1500];
        memset(packet, 0, sizeof(packet));

        struct iphdr *rip = (struct iphdr *)packet;
        struct udphdr *rup = (struct udphdr *)(packet + sizeof(struct iphdr));
        char *data = (char *)(rup + 1);

        int reply_len = strlen(reply);
        strcpy(data, reply);

        // IP header
        rip->ihl = 5;
        rip->version = 4;
        rip->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + reply_len);
        rip->protocol = IPPROTO_UDP;
        rip->saddr = ip->daddr;
        rip->daddr = ip->saddr;
        rip->ttl = 64;
        rip->check = 0;

        // UDP header
        rup->source = htons(SERVER_PORT);
        rup->dest = udp->source;
        rup->len = htons(sizeof(struct udphdr) + reply_len);
        rup->check = 0;

        struct sockaddr_in to = {0};
        to.sin_family = AF_INET;
        to.sin_addr = *(struct in_addr *)&ip->saddr;

        sendto(sockfd, packet, sizeof(struct iphdr) + sizeof(struct udphdr) + reply_len,
               0, (struct sockaddr *)&to, sizeof(to));
    }
}

