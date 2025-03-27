#include"threads.h"

void run(){
	pthread_t thread[N];
	int sum = 0;
	for(int i = 0; i < N; i++){
		pthread_create(&thread[i], NULL, summator, (void *)&sum);
	}
	for(int i = 0; i < N; i++){
		pthread_join(thread[i], NULL);
	}
	printf("Sum = %d", sum);
}

void *summator(void *args){
	int *sum = (int *) args;
	for(int i = 0; i < 1000000000/N; i++){
		(*sum)++;
	}
	return NULL;
}
