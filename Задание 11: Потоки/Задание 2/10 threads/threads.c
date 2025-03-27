#include"threads.h"

void run(){
	pthread_t thread[10];
	int sum = 0;
	for(int i = 0; i < 10; i++){
		pthread_create(&thread[i], NULL, summator, (void *)&sum);
	}
	for(int i = 0; i < 10; i++){
		pthread_join(thread[i], NULL);
	}
	printf("Sum = %d", sum);
}

void *summator(void *args){
	int *sum = (int *) args;
	for(int i = 0; i < 100000000; i++){
		(*sum)++;
	}
	return NULL;
}
