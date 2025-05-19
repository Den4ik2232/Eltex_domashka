#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main() {
    int fd, flag = 1;
    struct sockaddr_in serv;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag)) < 0) {
        perror("setsockopt");
        close(fd);
        exit(1);
    }
    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("255.255.255.255"); 
    printf("Server started! Sending to 255.255.255.255:12345");

    while (1) {
        ssize_t sent = sendto(fd, "Hello!", 7, 0,
                              (struct sockaddr *)&serv, sizeof(serv));
        if (sent < 0) {
            perror("sendto");
        } else {
            printf("Broadcast message sent: Hello!");
        }

        sleep(2);
    }

    close(fd);
    return 0;
}
