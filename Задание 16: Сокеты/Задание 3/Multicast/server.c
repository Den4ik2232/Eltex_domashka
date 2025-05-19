#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int fd;
    struct sockaddr_in serv;
    int ttl = 1;  // 1 = только внутри локальной сети

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }

    if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0) {
        perror("setsockopt");
        close(fd);
        exit(1);
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("239.0.0.1"); // диапазон 224.0.0.0 — 239.255.255.255

    printf("Server started! Sending to 239.0.0.1:12345\n");

    while (1) {
        ssize_t sent = sendto(fd, "Hello!", 7, 0,
                              (struct sockaddr *)&serv, sizeof(serv));
        if (sent < 0) {
            perror("sendto");
        } 

        sleep(2);
    }

    close(fd);
    return 0;
}
