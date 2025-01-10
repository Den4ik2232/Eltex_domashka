#include<stdio.h>

#define N 9

int main(){
int matrix[N];
for(int i = 0; i < N; i++){
matrix[i]=i+1;
}
for(int i = 0; i < N; i++){
printf("%d ", matrix[i]);
}
printf("\n");
int a;
for(int i = 0; i < N / 2; i++){
a = matrix[i];
matrix[i] = matrix[N-i-1];
matrix[N-i-1] = a;
}
for(int i = 0; i < N; i++){
printf("%d ", matrix[i]);
}}
