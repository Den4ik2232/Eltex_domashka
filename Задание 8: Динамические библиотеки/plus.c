#include "calculator.h"

void plus(){
	int a, b;
	read_two_number(&a, &b);
	printf("%d + %d = %d\n", a, b,  a + b);
}
