#include<stdio.h>

#define N 10
#define M 10

int main(){
int matrix[N][M] = {0};
int count = N - 1;
for(int i = 0; i < N; i++){
for(int j = count; j < M; j++){
matrix[i][j] = 1;
}
count--;
}
for(int i = 0; i < N; i++){
for(int j = 0; j < M; j++){
printf("%d ", matrix[i][j]);
}
printf("\n");
}
}
