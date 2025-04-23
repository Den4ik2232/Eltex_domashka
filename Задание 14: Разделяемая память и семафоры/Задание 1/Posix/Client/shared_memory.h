#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include<stdio.h>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include<stdlib.h>
struct msg {
	char msg_shm[2][10];
};

void run();

#endif // SHARED_MEMORY_H
