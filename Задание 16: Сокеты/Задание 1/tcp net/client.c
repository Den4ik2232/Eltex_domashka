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

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");  // локальный IP

    if (connect(fd, (struct sockaddr *) &serv, sizeof(serv)) < 0) {
        perror("connect");
        return 1;
    }

    send(fd, "Hi!", 128, 0);
    recv(fd, buf, sizeof(buf), 0);
    printf("Server: %s\n", buf);

    send(fd, "quit", 4, 0);

    close(fd);
    return 0;
}
