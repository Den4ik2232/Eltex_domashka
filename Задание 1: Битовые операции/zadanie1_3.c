#include<stdio.h>

int main(){
unsigned int n;
scanf("%d", &n);
int count = 0;
for(int i = 0; i < 32; i++){
if(n << i >> 31 == 1) count++;
}
printf("%d", count);
}
