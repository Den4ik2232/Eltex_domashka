#include"shared_memory.h"

void run(){
	key_t key_shm = ftok("./server", 1);
	if(key_shm == -1) perror("ftok");
	int shm_id = shmget(key_shm, sizeof(struct msg), 0660);
	if(shm_id == -1) perror("shmget");
	struct msg *message = (struct msg *) shmat(shm_id, NULL, 0);
	if(message == (struct msg *) -1) perror("shmat");
	strcpy(message->msg_shm[1], "Hello!");
	if(message->msg_shm[0][0]){
		printf("%s", message->msg_shm[0]);
	}
	shmdt((void *) message);
}
