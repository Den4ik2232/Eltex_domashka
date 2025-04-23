#ifndef MESSAGE_CHAT_H
#define MESSAGE_CHAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_CLIENTS 5
#define MAX_LEN_MESSAGE 128
#define MAX_COUNT_MESSAGE 128
#define SERVER_QUEUE   "/chat_server"

typedef struct {
    char name[32];
    char queue_name[64];
} ClientInfo;

void del_client(char name[32], char queue_name[64]);
void *listen_clients(void *args);
void send_to_all_clients(const char *msg);
void start();
void send_user_list();

#endif // MESSAGE_CHAT_H
