#include "calculator.h"

void division(){
	int a, b;
	read_two_number(&a, &b);
	printf("%d / %d = %.3f\n", a, b, (float)a / b);
}
