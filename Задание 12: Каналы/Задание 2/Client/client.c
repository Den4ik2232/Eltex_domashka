#include"client.h"

void run(){
	int fd = open("./pipe", O_RDONLY);
	if(fd < 0){
		perror("open");
		exit(1);
	}
	char symb;
	while(read(fd, &symb, 1) > 0) write(0, &symb, 1);
	close(fd);
	exit(1);
}
