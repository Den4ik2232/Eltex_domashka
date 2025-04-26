#include"sign.h"

void hdl(int signum, siginfo_t *info, void *context) {
    printf("Получен сигнал %d\n", signum);
}

void run() {
    struct sigaction act = {0};

    act.sa_sigaction = hdl;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;  

    if (sigaction(SIGUSR1, &act, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    int pid = getpid(); 
    printf("wait signal... pid = %d\n", pid);

    while (1) {
        pause();
    }
}
