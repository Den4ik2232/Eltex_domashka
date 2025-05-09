#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(){
	int fd_serv, fd_client;
	struct sockaddr_un serv, client;
	socklen_t client_len;

	fd_serv = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(fd_serv < 0){
		perror("socket");
		return 1;
	}

	unlink("./server");

	serv.sun_family = AF_LOCAL;
	strncpy(serv.sun_path, "./server", sizeof(serv.sun_path) - 1);

	if(bind(fd_serv, (struct sockaddr *) &serv, sizeof(serv)) < 0){
		perror("bind");
		return 1;
	}

	listen(fd_serv, 2);

	client_len = sizeof(client);
	fd_client = accept(fd_serv, (struct sockaddr *) &client, &client_len);
	if(fd_client < 0){
		perror("accept");
		return 1;
	}

	char buf[128];
	recv(fd_client, buf, 128, 0);
	printf("%s\n", buf);
	send(fd_client, "Hello!", 6, 0);
	recv(fd_client, buf, 128, 0);

	close(fd_client);
	close(fd_serv);
	return 0;
}
