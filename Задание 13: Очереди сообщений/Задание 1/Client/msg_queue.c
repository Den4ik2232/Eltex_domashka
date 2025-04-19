#include"msg_queue.h"

void run(){
	key_t key_msg_server;
	int msg_id_server;
	if((key_msg_server = ftok("./server", 1)) == -1){
		perror("ftok: client");
	}
	//key_msg_client = ftok("./client", 1);
	if((msg_id_server = msgget(key_msg_server, 0)) == -1){
		perror("msgget:client");
	}
	//msg_id_client = msgget(key_msg_client, IPC_CREAT);
	struct msg_buf msg_send, msg_receive;
	msg_send.msg_text[0] = 'H';
	msg_send.msg_text[1] = 'i';
	msg_send.msg_text[2] = '!';
	msg_send.mtype = 2;
	if(msgrcv(msg_id_server, &msg_receive, 10, 1, 0) == -1){
		perror("msgrcv: client");
	}
	printf("%s", msg_receive.msg_text);
        if(msgsnd(msg_id_server, &msg_send, 10, 0) == -1){
		perror("msgsnd: client");
	}
	//msgctl(msg_id_client, IPC_RMID, NULL);
}
