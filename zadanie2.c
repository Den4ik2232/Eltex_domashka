#include<stdio.h>

int main(){
int n;
scanf("%d", &n);
char c;
for(int i = 31; i >= 0; i--){
c = n >> i & 1;
printf("%x", c);
}
}
