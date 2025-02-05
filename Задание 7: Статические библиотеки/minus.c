#include "calculator.h"

void minus(){
	int a, b;
	read_two_number(&a, &b);
	printf("%d - %d = %d\n", a, b, a - b);
}
