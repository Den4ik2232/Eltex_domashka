#include"msg_queue.h"

void run(){
	mqd_t qd_msg1, qd_msg2;
	if((qd_msg1 = mq_open("/queue_1", O_RDONLY, 0660, NULL)) == -1){
		perror("mq_open1 client");
		exit(1);
	}
	if((qd_msg2 = mq_open("/queue_2", O_WRONLY, 0660, NULL)) == -1){
                perror("mq_open2 client");
                exit(1);
        }
	char msg_send[10], msg_receive[10];
	msg_send[0] = 'H'; msg_send[1] = 'e'; msg_send[2] = 'l'; msg_send[3] = 'l'; msg_send[4] = 'o'; msg_send[5] = '!';
	if(mq_receive(qd_msg1, msg_receive, 10, 0) == -1){
		perror("mq_receive client");
		exit(1);
	}
	printf("Server message %s\n", msg_receive);
	if(mq_send(qd_msg2, msg_send, 10, 0) == -1){
		perror("mq_send server");
		exit(1);
	}
	printf("Client send message!\n");
	mq_unlink("/queue_1");
	mq_unlink("/queue_2");
}

