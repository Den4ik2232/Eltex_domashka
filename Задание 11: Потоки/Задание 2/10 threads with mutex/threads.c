#include"threads.h"

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void run(){
	pthread_t thread[10];
	long sum = 0;
	for(int i = 0; i < 10; i++){
		pthread_create(&thread[i], NULL, summator, (void *)&sum);
	}
	for(int i = 0; i < 10; i++){
		pthread_join(thread[i], NULL);
	}
	printf("Sum = %ld", sum);
}

void *summator(void *args){
	long *sum = (long *) args;
	for(int i = 0; i < 100000000; i++){
		pthread_mutex_lock(&m);
		(*sum)++;
		pthread_mutex_unlock(&m);
	}
	return NULL;
}
