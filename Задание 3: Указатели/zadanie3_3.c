#include <stdio.h>
int main(void)
{
int massiv[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int *ukaz = massiv;
for(int i = 0; i < 10; i++){
printf("%d ", *ukaz);
ukaz++;
} 
}
