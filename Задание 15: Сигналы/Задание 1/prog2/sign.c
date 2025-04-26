#include"sign.h"

void run(){
	printf("Введите pid процессора которому отправить сигнал - ");
	int pid;
	scanf("%d", &pid);
	int signum;
	printf("Введите номер сигнала - ");
	scanf("%d", &signum);
	kill(pid, signum);
	printf("Сигнал отправлен!\n");
}
