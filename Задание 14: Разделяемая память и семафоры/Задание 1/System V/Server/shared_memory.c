#include"shared_memory.h"

void run(){
	key_t key_shm = ftok("./server", 1);
	if(key_shm == -1) perror("ftok");
	int shm_id = shmget(key_shm, sizeof(struct msg), 0660 | IPC_CREAT);
	if(shm_id == -1) perror("shmget");
	struct msg *message;
	if((message = (struct msg *) shmat(shm_id, NULL, 0)) == (struct msg *) -1) perror("shmat");
	strcpy(message->msg_shm[0], "Hi!");
	while(1){
		if(message->msg_shm[1][0]){
			printf("%s", message->msg_shm[1]);
			break;
		}
	}
	shmdt((void *) message);
	shmctl(shm_id, IPC_RMID, 0);
}
