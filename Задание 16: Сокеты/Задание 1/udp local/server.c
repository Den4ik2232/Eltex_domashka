#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(){
    int fd;
    struct sockaddr_un serv, client;
    socklen_t client_len;
    char buf[128];
    fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(fd < 0){
        perror("socket");
        return 1;
    }
    unlink("./server");
    serv.sun_family = AF_LOCAL;
    strncpy(serv.sun_path, "./server", sizeof(serv.sun_path) - 1);
    if(bind(fd, (struct sockaddr *) &serv, sizeof(serv)) < 0){
        perror("bind");
        return 1;
    }
    client_len = sizeof(client);
    recvfrom(fd, buf, 128, 0, (struct sockaddr *) &client, &client_len);
    printf("Client: %s\n", buf);
    sendto(fd, "Hello!", 128, 0, (struct sockaddr *) &client, client_len);
    recvfrom(fd, buf, 128, 0, (struct sockaddr *) &client, &client_len);
    close(fd);
    unlink("./server");
    return 0;
}
