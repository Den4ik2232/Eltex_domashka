#include "server.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <errno.h>

#define MAX_CLIENTS 100

typedef struct {
    struct sockaddr_in addr;
    int msg_count;
} Client;

Client clients[MAX_CLIENTS];
int client_count = 0;

int find_or_add_client(struct sockaddr_in *addr) {
    for (int i = 0; i < client_count; ++i) {
        if (clients[i].addr.sin_addr.s_addr == addr->sin_addr.s_addr &&
            clients[i].addr.sin_port == addr->sin_port) {
            return i;
        }
    }
    if (client_count < MAX_CLIENTS) {
        clients[client_count].addr = *addr;
        clients[client_count].msg_count = 0;
        return client_count++;
    }
    return -1;
}

void remove_client(struct sockaddr_in *addr) {
    for (int i = 0; i < client_count; ++i) {
        if (clients[i].addr.sin_addr.s_addr == addr->sin_addr.s_addr &&
            clients[i].addr.sin_port == addr->sin_port) {
            clients[i] = clients[--client_count];
            return;
        }
    }
}

void run_server() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    printf("Server running, port = %d\n", SERVER_PORT);

    char buffer[MAX_MSG_LEN];
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (1) {
        ssize_t recv_len = recvfrom(sockfd, buffer, MAX_MSG_LEN - 1, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (recv_len < 0) {
            perror("recvfrom");
            continue;
        }
        buffer[recv_len] = '\0';

        if (strcmp(buffer, CLOSE_MSG) == 0) {
            printf("Client disconnect: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            remove_client(&client_addr);
            continue;
        }

        int id = find_or_add_client(&client_addr);
        if (id == -1) {
            printf("Too many clients!!!\n");
            continue;
        }
        clients[id].msg_count++;

        char response[MAX_MSG_LEN];
        snprintf(response, sizeof(response), "%s %d", buffer, clients[id].msg_count);

        sendto(sockfd, response, strlen(response), 0,
               (struct sockaddr*)&client_addr, addr_len);
    }

    close(sockfd);
}
