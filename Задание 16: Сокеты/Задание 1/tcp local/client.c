#include<stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include<string.h>

int main(){
	int fd;
	struct sockaddr_un serv;
	fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(fd < 0){
		perror("socket");
	}
	serv.sun_family = AF_LOCAL;
	strncpy(serv.sun_path, "./server", sizeof(serv.sun_path) - 1);
	if(connect(fd, (struct sockaddr *) &serv, sizeof(serv)) == -1){
		perror("connect");	
	}
	char buf[128];
	send(fd, "Hi!", 128, 0);
	recv(fd, buf, 128, 0);
	printf("%s", buf);
	send(fd, "quit", 4, 0);
	close(fd);
	return 0;
}

