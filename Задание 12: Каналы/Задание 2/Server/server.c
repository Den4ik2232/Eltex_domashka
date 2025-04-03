#include"server.h"

void run(){
	int fd;
	if(mkfifo("./pipe", 0777) < 0){
		perror("mkfifo");
		exit(1);
	}
	fd = open("./pipe", O_WRONLY);
	if(fd < 0){
		perror("open");
		exit(1);
	}
	if(write(fd, "Hi!", 4) < 0){
		perror("write");
	}
	close(fd);
	unlink("./pipe");
	exit(1);
}
