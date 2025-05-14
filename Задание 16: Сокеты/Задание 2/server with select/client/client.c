#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_SOCKET_PATH "./server_socket"
#define CLIENT_SOCKET_PATH "./client_socket"

int main() {
    int sockfd;
    struct sockaddr_un server_addr, client_addr;
    char buffer[128];

    unlink(CLIENT_SOCKET_PATH);

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, CLIENT_SOCKET_PATH, sizeof(client_addr.sun_path) - 1);
    if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    sendto(sockfd, "Hi!", 4, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    int n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Received time: %s\n", buffer);
    } else {
        printf("No response received.\n");
    }

    close(sockfd);
    unlink(CLIENT_SOCKET_PATH);
    return 0;
}
