#include <stdio.h>


int main() {
  int number;
  printf("Введите целое положительное число: ");
  scanf("%d", &number);
  if(number < 0) printf("ERROR");
  else{
	  char *ukaz = &number;
	  ukaz += 2;
	  int new_val;
	  printf("Введите значение 3-его байта от 0 до 255: ");
	  scanf("%d", &new_val);
	  if(new_val < 0 || new_val > 255) printf("ERROR");
	  else{
	  	*ukaz = new_val;
	  	printf("Полученное число: %d", number);
	  }
  }	
  }

