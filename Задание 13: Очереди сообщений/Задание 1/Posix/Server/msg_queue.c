#include"msg_queue.h"

void run(){
	struct mq_attr attr;
    	attr.mq_flags = 0;
    	attr.mq_maxmsg = 5;
    	attr.mq_msgsize = 10;
    	attr.mq_curmsgs = 0;
	mqd_t qd_msg1, qd_msg2;
	mq_unlink("/queue_1");
        mq_unlink("/queue_2");
	if((qd_msg1 = mq_open("/queue_1", O_WRONLY | O_CREAT, 0660, &attr)) == -1){
		perror("mq_open1 server");
		exit(1);
	}
	if((qd_msg2 = mq_open("/queue_2", O_RDONLY | O_CREAT, 0660, &attr)) == -1){
                perror("mq_open2 server");
                exit(1);
        }
	char msg_send[10], msg_receive[10];
	msg_send[0] = 'H'; msg_send[1] = 'i';
	if(mq_send(qd_msg1, msg_send, 10, 0) == -1){
		perror("mq_send server");
		exit(1);
	}
	printf("Server send message!\n");
	if(mq_receive(qd_msg2, msg_receive, 10, 0) == -1){
		perror("mq_receive server");
		exit(1);
	}
	printf("Client message: %s\n", msg_receive);
	mq_unlink("/queue_1");
	mq_unlink("/queue_2");
}
