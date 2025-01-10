#include<stdio.h>

#define N 10
#define M 10

int main(){
int matrix[N][M];
int n = 1;
for(int i = 0; i < N; i++){
	for(int j = 0; j < M; j++){
		matrix[i][j] = n;
		n++;}}
for(int i = 0; i < N; i++){
	for(int j = 0; j < M; j++){
		printf("%d\t", matrix[i][j]);}
	printf("\n");
}}
