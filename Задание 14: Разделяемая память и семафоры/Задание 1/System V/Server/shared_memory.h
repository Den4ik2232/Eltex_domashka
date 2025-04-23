#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include<stdio.h>
#include <sys/shm.h>
#include <string.h>
struct msg {
	char msg_shm[2][10];
};

void run();

#endif // SHARED_MEMORY_H
