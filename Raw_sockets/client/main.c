#include "client.h"
#include<stdio.h>
#include<string.h>

int main(){
    printf("Enter SERVER IP: ");
    char ip_server[16];
    fgets(ip_server, sizeof(ip_server), stdin);
    ip_server[strcspn(ip_server, "\n")] = 0;
    run_client(ip_server);
    return 0;
}
