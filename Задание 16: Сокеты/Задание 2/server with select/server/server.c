#include"server.h"
#define SOCKET_PATH "./server_socket"
#define BUF_SIZE 128

void run() {
    int sockfd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUF_SIZE];

    unlink(SOCKET_PATH);

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    printf("Server is running on %s...\n", SOCKET_PATH);

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);
        if (activity < 0) {
            perror("select");
            break;
        } else if (activity == 0) {
            printf("No data within 5 seconds...\n");
            continue;
        }

        if (FD_ISSET(sockfd, &readfds)) {
            ssize_t n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                                 (struct sockaddr *)&client_addr, &client_len);
            if (n < 0) {
                perror("recvfrom");
                continue;
            }

            buffer[n] = '\0';
            printf("Received: %s\n", buffer);

            time_t now = time(NULL);
            struct tm *tm_info = localtime(&now);
            char time_str[BUF_SIZE];
            snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d",
                     tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

            sendto(sockfd, time_str, strlen(time_str), 0,
                   (struct sockaddr *)&client_addr, client_len);
            printf("Time sent to client!\n");
        }
    }

    close(sockfd);
    unlink(SOCKET_PATH);
    return 0;
}
