#include<stdio.h>

int main(){
int n;
printf("Введите число - ");
scanf("%d", &n);
int izm = 31;
printf("Введите число на которое хотите поменять третий байт - ");
scanf("%d", &izm);
izm = (izm << 16);
n = n & 0xFF00FFFF;
n = n | izm;
printf("Полученное число - %d\n", n);
char c;
for(int i = 31; i >= 0; i--){
c = (n >> i) & 1;
printf("%x", c); 
}
}
