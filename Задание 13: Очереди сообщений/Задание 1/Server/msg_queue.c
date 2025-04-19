#include"msg_queue.h"

void run(){
	key_t key_msg_server;
        int msg_id_server;
        key_msg_server = ftok("./server", 1);
        //key_msg_client = ftok("./client", 1);
        if((msg_id_server = msgget(key_msg_server, IPC_CREAT)) == -1){
		perror("msgget: server");
		exit(1);
	}
        /*if((msg_id_client = msgget(key_msg_client, 0)) == -1){
		perror("msgget: client");
		exit(1);
	}*/
        struct msg_buf msg_send, msg_receive;
        msg_send.msg_text[0] = 'H';
	msg_send.msg_text[1] = 'e';
	msg_send.msg_text[2] = 'l';
	msg_send.msg_text[3] = 'l';
        msg_send.msg_text[4] = 'o';
        msg_send.mtype = 1;
        if(msgsnd(msg_id_server, &msg_send, 10, 0) == -1){
		perror("msgsnd: server");
		exit(1);
	}
        //printf("%s", msg_receive.msg_text);
        if(msgrcv(msg_id_server, &msg_receive, 10, 2, 0) == -1){
		perror("msgrcv: server");
		exit(1);
	}	
	printf("%s", msg_receive.msg_text);
        if(msgctl(msg_id_server, IPC_RMID, NULL) == -1){
		perror("msgctl: server");
		exit(1);
	}
}
