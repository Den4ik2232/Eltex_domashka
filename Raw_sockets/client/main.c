#include "client.h"
#include <stdio.h>
#include <string.h>

int main() {
    char ip_server[17];
    printf("Enter SERVER IP: ");
    if (fgets(ip_server, sizeof(ip_server), stdin) == NULL) {
        fprintf(stderr, "Failed to read IP\n");
        return 1;
    }
    ip_server[strcspn(ip_server, "\n")] = '\0';
    printf("Connecting to: %s\n", ip_server);
    run_client(ip_server);
    return 0;
}
