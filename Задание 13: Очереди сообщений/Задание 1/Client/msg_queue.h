#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <sys/msg.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>

struct msg_buf{
	long mtype;
	char msg_text[10];
};

void run();

#endif // MSG_QUEUE_H
