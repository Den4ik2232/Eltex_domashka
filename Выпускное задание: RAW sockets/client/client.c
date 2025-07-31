#include "client.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void run_client() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_aton(SERVER_IP, &server_addr.sin_addr);

    char buffer[MAX_MSG_LEN], recv_buf[MAX_MSG_LEN];

    while (1) {
        printf("Enter message or /exit: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        
	buffer[strcspn(buffer, "\n")] = 0;
        
	
	if (strcmp(buffer, "/exit") == 0) {
            sendto(sockfd, CLOSE_MSG, strlen(CLOSE_MSG), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
            break;
        }


        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        socklen_t addr_len = sizeof(server_addr);
        ssize_t recv_len = recvfrom(sockfd, recv_buf, MAX_MSG_LEN - 1, 0, (struct sockaddr*)&server_addr, &addr_len);
        if (recv_len > 0) {
            recv_buf[recv_len] = '\0';
            printf("Server: %s\n", recv_buf);
        }
    }

    close(sockfd);
}
