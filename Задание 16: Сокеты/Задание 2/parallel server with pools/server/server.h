#ifndef SERVER_H
#define SERVER_H

#include<stdio.h>
#include<pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include<time.h>
#include<stdlib.h>

void run();
void *thread_server(void *args);

#endif //SERVER_H
