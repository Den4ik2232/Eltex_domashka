#include<stdio.h>

#define N 5

int main(){
int matrix[N][N];
int k = 1, start_x = 0, start_y = 0, stop_x = N - 1, stop_y = N - 1;
while(k <= N * N){
for(int i = start_y; i <= stop_y && k <= N * N; i++){
matrix[start_x][i] = k;
k++;
}
start_x++;
for(int i = start_x; i <= stop_x && k <= N * N; i++){
matrix[i][stop_y] = k;
k++;
}
stop_y--;
for(int i = stop_y; i >= start_y && k <= N * N; i--){
matrix[stop_x][i] = k;
k++;
}
stop_x--;
for(int i = stop_x; i >= start_x && k <= N * N; i--){
matrix[i][start_y] = k;
k++;
}
start_y++;
}
for(int i = 0; i < N; i++){
for(int j = 0; j < N; j++){
printf("%d\t", matrix[i][j]);
}
printf("\n");
}
}
