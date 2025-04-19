#ifndef MESSAGE_CHAT_H
#define MESSAGE_CHAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <pthread.h>
#include <unistd.h>

#define SERVER_QUEUE  "/chat_server"
#define MAX_MSG_SIZE  1024
#define MAX_CLIENTS 5
void run();
void *receive_messages(void *arg);



#endif //MESSAGE_CHAT_H
