#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int fd;
    struct sockaddr_in serv, client;
    socklen_t client_len;
    char buf[128];

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(12345);

    if (bind(fd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind");
        return 1;
    }

    client_len = sizeof(client);
    recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&client, &client_len);
    printf("Client: %s\n", buf);

    sendto(fd, "Hello!", 128, 0, (struct sockaddr *)&client, client_len);

    recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&client, &client_len);

    close(fd);
    return 0;
}
