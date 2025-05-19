#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int fd;
    struct sockaddr_in client;
    char buffer[128];

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(12345);

    if (bind(fd, (struct sockaddr *)&client, sizeof(client)) < 0) {
        perror("bind");
        close(fd);
        exit(1);
    }
    while (1) {
        ssize_t n = recv(fd, buffer, sizeof(buffer) - 1, 0);
        if (n < 0) {
            perror("recv");
            continue;
        }

        buffer[n] = '\0';
        printf("Received: %s\n", buffer);
    }

    close(fd);
    return 0;
}
