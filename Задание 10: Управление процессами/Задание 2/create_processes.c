#include"create_processes.h"
/*Реализовать программу, которая порождает процесс1 и процесс2, ждет
завершения дочерних процессов. Процесс1 в свою очередь порождает
процесс3 и процесс4 и ждет их завершения. Процесс2 порождает
процесс5 и ждет его завершения. Все процессы выводят на экран свой
pid, ppid.*/
void run(){
	int status1, status2, status3, status4, status5;
	pid_t child_pid_0_1, child_pid_0_2;
	
	child_pid_0_1 = fork();
	if(child_pid_0_1 < 0) exit(0);
	if(child_pid_0_1 != 0){
		printf("pid process 0 = %d\nppid process 0 = %d\n", getpid(), getppid());
		child_pid_0_2 = fork();
		if(child_pid_0_2 < 0) exit(0);
		if(child_pid_0_2 != 0){
			waitpid(child_pid_0_2, &status2, 0);
			printf("Status2 = %d\n", WEXITSTATUS(status2));
		}
		else{
			printf("pid process 2 = %d\nppid process 2 = %d\n", getpid(), getppid());
			pid_t child_pid_2_5;
			child_pid_2_5 = fork();
			if(child_pid_2_5 < 0) exit(0);
			if(child_pid_2_5 != 0){
				wait(&status5);
				printf("Status5 = %d\n", WEXITSTATUS(status5));
				exit(2);
			}
			else{
				printf("pid process 5 = %d\nppid process 5 = %d\n", getpid(), getppid());
				exit(5);
			}
		}
		waitpid(child_pid_0_1, &status1, 0);
		printf("Status1 = %d\n", WEXITSTATUS(status1));
	}
	else{
		pid_t child_pid_1_3;
		child_pid_1_3 = fork();
		if(child_pid_1_3 < 0) exit(0);
		if(child_pid_1_3 == 0){
			printf("pid process 3 = %d\nppid process 3 = %d\n", getpid(), getppid());
			exit(3);
		}
		else{
			pid_t child_pid_1_4;
			child_pid_1_4 = fork();
			if(child_pid_1_4 < 0) exit(0);
			if(child_pid_1_4 == 0){
				printf("pid process 4 = %d\nppid process 4 = %d\n", getpid(), getppid());
				exit(4);
			}
			else{
				waitpid(child_pid_1_4, &status4, 0);
				waitpid(child_pid_1_3, &status3, 0);
				printf("status3 = %d\nstatus4 = %d\n", WEXITSTATUS(status3), WEXITSTATUS(status4));
				printf("pid process 1 = %d\nppid process 1 = %d\n", getpid(), getppid());
				exit(1);
			}
		
		}
	
	}



}
