#include"sign.h"

void run(){
	sigset_t set;
    	int sig;

    	sigemptyset(&set);
    	sigaddset(&set, SIGUSR1);

    	if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
        	perror("sigprocmask");
        	exit(EXIT_FAILURE);
    	}

    	printf("Ожидание SIGUSR1... PID = %d\n", getpid());

    	while (1) {
        	if (sigwait(&set, &sig) != 0) {
            	perror("sigwait");
            	exit(EXIT_FAILURE);
        	}

        	printf("Получен сигнал %d\n", sig);
    	}

}
