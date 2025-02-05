#include<stdio.h>
#include"./calculator.h"



int main(){
	int choice = 0;
	do {
    		printf(
      		"1) Выполнить сложение\n"
     		"2) Выполнить вычитание\n"
      		"3) Выполнить умножение\n"
      		"4) Выполнить деление\n"
      		"5) Выход\n");
    		if (scanf("%d", &choice) != 1) {
   		 printf("Ошибка ввода!\n");
   		 continue;
}

    		switch (choice) {
      			case 1:
        			plus();
        			break;
      			case 2:
        			minus();
        			break;
      			case 3:
        			multiplication();
        			break;
      			case 4:
        			division();
        			break;
      			case 5:
        			printf("Завершение программы...\n");
        			break;
      			default:
        			printf("Ошибка! Неверное значение пункта меню.\n");
        			break;
    			}
  	} while (choice != 5);
}




