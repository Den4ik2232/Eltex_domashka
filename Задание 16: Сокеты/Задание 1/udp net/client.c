#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int fd;
    struct sockaddr_in serv;
    char buf[128];

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(fd, "Hi!", 128, 0, (struct sockaddr *)&serv, sizeof(serv));
    recvfrom(fd, buf, 128, 0, NULL, NULL);
    printf("Server: %s\n", buf);
    sendto(fd, "quit", 128, 0, (struct sockaddr *)&serv, sizeof(serv));

    close(fd);
    return 0;
}
