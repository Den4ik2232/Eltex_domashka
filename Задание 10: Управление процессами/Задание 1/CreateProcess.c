#include"CreateProcess.h"
//Реализовать программу, которая порождает процесс. Родительский
//процесс и дочерний выводят на экран свой pid, ppid. Затем родительский
//ждет завершения дочернего и выводит его статус завершения.
void run(){
	pid_t child_pid;
	int status;

	child_pid = fork();
	if(child_pid < 0) exit(0);
	if(child_pid == 0){
		printf("Child pid = %d\nParent pid =%d\n", getpid(), getppid());
		exit(5);
	}
	else{
		printf("Parent pid = %d\nGrandparent pid = %d\n", getpid(), getppid());
		wait(&status);
		printf("Status = %d\n", WEXITSTATUS(status));
	}
}
