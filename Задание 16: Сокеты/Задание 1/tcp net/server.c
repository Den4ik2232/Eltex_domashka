#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int fd_serv, fd_client;
    struct sockaddr_in serv, client;
    socklen_t client_len;
    char buf[128];

    fd_serv = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_serv < 0) {
        perror("socket");
        return 1;
    }

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY; 
    serv.sin_port = htons(12345);     

    if (bind(fd_serv, (struct sockaddr *) &serv, sizeof(serv)) < 0) {
        perror("bind");
        return 1;
    }

    listen(fd_serv, 2);

    client_len = sizeof(client);
    fd_client = accept(fd_serv, (struct sockaddr *) &client, &client_len);
    if (fd_client < 0) {
        perror("accept");
        return 1;
    }

    recv(fd_client, buf, sizeof(buf), 0);
    printf("Client: %s\n", buf);

    send(fd_client, "Hello!", 128, 0);

    recv(fd_client, buf, sizeof(buf), 0);

    close(fd_client);
    close(fd_serv);

    return 0;
}
