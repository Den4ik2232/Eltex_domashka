#include<stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include<string.h>

int main(){
	int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
	struct sockaddr_un addr;
	addr.sun_family = AF_LOCAL;
	strcpy(addr.sun_path, "./server_socket");

	connect(sock, (struct sockaddr*)&addr, sizeof(addr));

	send(sock, "Hi!", 3, 0);

	char buf[128] = {0};
	ssize_t n = recv(sock, buf, sizeof(buf), 0);
	if (n > 0) {
    		printf("Received time: %s\n", buf);
	} else {
    		printf("Failed to receive data\n");
	}

	close(sock);
}

