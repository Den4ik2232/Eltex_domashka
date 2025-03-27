#include"life.h"

int shop[5];
pthread_mutex_t m[5];

void run(){
	for(int i = 0; i < 5; i++){
		pthread_mutex_init(&m[i], NULL);
	}
	pthread_t threads_customers[3];
	pthread_t threads_shop_loader;
	int customers[3];
	for(int i = 0; i < 5; i++){
		shop[i] = 9000 + rand() % 2000;
		srand(i * 100);
	}	
	for(int i = 0; i < 3; i++){
		customers[i] = i;
		pthread_create(&threads_customers[i], NULL, thread_customer, (void *)&customers[i]);	
	}
	pthread_create(&threads_shop_loader, NULL, thread_shop_loader, NULL);
	for(int i = 0; i < 3; i++){
		pthread_join(threads_customers[i], NULL);
	}
	pthread_cancel(threads_shop_loader);
	return NULL;
}

void *thread_customer(void *args){
	int *num_customer = (int *) args;
	*num_customer += 1;
	int needs = 95000 + rand() % 10000;
	while(1){
		for(int i = rand() % 5; i < 5; i++){	
			if(!pthread_mutex_trylock(&m[i])){
				printf("Я поток-покупатель №%d, у меня %d потребности, зашел в магазин №%d, в котором %d товаров\n\n", *num_customer, needs, i + 1, shop[i]);
				if(shop[i] < needs){
			       		needs -= shop[i];
					shop[i] = 0;
				}
				else{
					shop[i] -= needs;
					needs = 0;
				}
				pthread_mutex_unlock(&m[i]);
				printf("Я поток-покупатель №%d, теперь у меня %d потребности\n\n", *num_customer, needs);
				break;	
			}
		}
		if(needs == 0){
			printf("Поток покупатель №%d завершился\n\n", *num_customer);
                	return NULL;
		}
		sleep(10);
	}	
}

void *thread_shop_loader(void *args){
	while(1){
		for(int i = rand() % 5; i < 5; i++){
			if(!pthread_mutex_trylock(&m[i])){
				shop[i] += 5000;
				pthread_mutex_unlock(&m[i]);
				printf("Я поток-погрузчик, загрузил в магазин №%d 5000 товаров, в нем было %d, стало %d товаров\n\n", i + 1, shop[i] - 5000, shop[i]);
			break;
			}
		}
		sleep(1);
	}
}
