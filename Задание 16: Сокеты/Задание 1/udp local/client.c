#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    int fd;
    struct sockaddr_un serv, client;

    fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    unlink("./cl"); 
    client.sun_family = AF_LOCAL;
    strncpy(client.sun_path, "./cl", sizeof(client.sun_path) - 1);
    if (bind(fd, (struct sockaddr *)&client, sizeof(client)) < 0) {
        perror("bind");
        return 1;
    }

    serv.sun_family = AF_LOCAL;
    strncpy(serv.sun_path, "./server", sizeof(serv.sun_path) - 1);

    sendto(fd, "Hi!", 128, 0, (struct sockaddr *)&serv, sizeof(serv));
    char buf[128];
    recvfrom(fd, buf, 128, 0, NULL, NULL);
    printf("Server: %s\n", buf);
    sendto(fd, "quit", 128, 0, (struct sockaddr *)&serv, sizeof(serv));
    close(fd);
    unlink("./cl");
    return 0;
}
