#include"sign.h"

void run(){
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
    		perror("sigprocmask");
        	exit(EXIT_FAILURE);
    	}
    	printf("SIGINT заблокирован. PID = %d\n", getpid());
    	while (1) {
        	pause(); 
    	}
}
