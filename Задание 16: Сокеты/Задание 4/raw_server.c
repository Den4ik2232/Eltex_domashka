#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdlib.h>

int main() {
    int fd;
    unsigned char buf[65536];

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }

    while (1) {
        struct sockaddr_in client;
        socklen_t client_size = sizeof(client);
        ssize_t len = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&client, &client_size);
        if (len < 0) {
            perror("recvfrom");
            close(fd);
            exit(1);
        }
        //IP-заголовок
        struct iphdr *iph = (struct iphdr *)buf;
        int iphdr_len = iph->ihl * 4;
        //UDP-заголовок
        struct udphdr *udph = (struct udphdr *)(buf + iphdr_len);
        // Указатель на данные
        char *data = (char *)(buf + iphdr_len + sizeof(struct udphdr));
        int data_len = ntohs(udph->len) - sizeof(struct udphdr);
        printf("Получен UDP пакет-\n");
        printf("От: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(udph->source));
        printf("Куда: %d\n", ntohs(udph->dest));
        printf("Длина данных: %d байт\n", data_len);
        printf("Данные: %s\n", data);
    }

    close(fd);
    return 0;
}
