#include"threads.h"

void run(){
	int ind[5];	
	pthread_t thread[5];


	for(int i = 0; i < 5; i++){
		ind[i] = i;
		pthread_create(&thread[i], NULL, thread_index, (void *)&ind[i]);
	}
	for(int i = 0; i < 5; i++){
		pthread_join(thread[i], NULL);
	}
}

void *thread_index(void *args){
	int *ind = (int *) args;
	printf("Thread №%d finish\n", *ind);
	return NULL;
}
