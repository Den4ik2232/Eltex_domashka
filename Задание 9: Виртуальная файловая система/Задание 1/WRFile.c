#include"WRFile.h"


void run(){
	int fd = open("test.txt", O_RDWR | O_CREAT);
        if(fd == -1){
                printf("ERROR");
                exit(1);
        }

        int sz = write(fd, "String from file\0", 16);
        if(sz == 0 || sz == -1) {
                printf("ERROR");
                exit(1);
        }
        char* c = (char*)calloc(1, sizeof(char));
       for(int i = 16; i >= 0; i--){
       lseek(fd, i, SEEK_SET);
       if(read(fd, c, 1) != -1) printf("%s", c);
       }
        close(fd);
}
