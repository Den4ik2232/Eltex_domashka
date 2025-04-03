#include"pipes.h"
//Реализовать программу, которая создает неименованный канал и порождает процесс. Родительский процесс закрывает дескриптор для чтения из канала и записывает в канал строку “Hi!”, затем ожидает завершения дочернего процесса. Дочерний процесс закрывает дескриптор для записи в канал, считывает строку из канала и выводит на экран.
void run(){
	int pipefd[2];
	pid_t pid;
	if(pipe(pipefd) == -1){
		perror("pipe");
		exit(1);
	}
	//printf("%d %d", pipefd[0], pipefd[1]);
	pid = fork();
	if(pid > 0){
		close(pipefd[0]);
		write(pipefd[1], "Hi!", 3);
		close(pipefd[1]);
		wait(NULL);
		exit(1);	
	}
	else if(pid == 0){
		char symb;
		close(pipefd[1]);
		while(read(pipefd[0], &symb, 1) > 0) write(0, &symb, 1);
		close(pipefd[0]);
		exit(1);
	}
	else{
		perror("fork");
		exit(1);	
	}	
}
