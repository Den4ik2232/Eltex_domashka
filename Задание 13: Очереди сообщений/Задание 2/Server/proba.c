#include<stdio.h>
#include<string.h>

int main(){
	char command[50];
	fgets(command, sizeof(command), stdin);
	//char *command1 = strtok(NULL, "\n");
	printf("1 - %s\n", strtok(command, "\n"));
	if(strlen(command) == sizeof(command) - 1) while(getchar() != '\n');
	char a[10];
	fgets(a, 10, stdin);
	printf("2 - %s\n", a);
}
