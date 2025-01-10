#include<stdio.h>

int main(){
unsigned int n;
char c;
scanf("%d", &n);
for(int i = 0; i < 32; i++){
c = n << i >> 31;
printf("%x", c);
}
}
