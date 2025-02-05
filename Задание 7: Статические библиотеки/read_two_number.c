#include "calculator.h"

void read_two_number(int* a, int* b){
	while(1){
		printf("Введите первое число(целое): ");
		if(!scanf("%d", a)) {printf("Ошибка ввода! Попробуйте еще раз! \n"); while(getchar() != '\n' && getchar() != EOF); continue;}
		printf("Введите второе число(целое):");
		if(!scanf("%d", b)) {printf("Ошибка ввода! Попробуйте еще раз! \n"); while(getchar() != '\n' && getchar() != EOF); continue;}
		break;
	}
}
