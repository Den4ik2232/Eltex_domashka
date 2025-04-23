#ifndef MESSAGE_CHAT_H
#define MESSAGE_CHAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>


#define MAX_CLIENTS 5
#define MAX_MESSAGES 128
#define MAX_MSG_LEN 128
#define MAX_NAME_LEN 32

#define SHM_NAME "/chat_shm"
#define SEM_MUTEX "/chat_sem_mutex"
#define SEM_MSG "/chat_sem_msg"
#define SEM_UPDATE "/chat_sem_update"

typedef struct {
    char sender[MAX_NAME_LEN];
    char content[MAX_MSG_LEN];
} ChatMessage;

typedef struct {
    char names[MAX_CLIENTS][MAX_NAME_LEN];
    int connected[MAX_CLIENTS];
    ChatMessage messages[MAX_MESSAGES];
    int message_count;
} ChatData;

void run();

#endif // MESSAGE_CHAT_H
