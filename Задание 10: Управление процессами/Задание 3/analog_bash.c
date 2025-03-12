#include "analog_bash.h"

void run_command(char *command) {
    char *args[MAX_ARGS_COUNT];
    char *stroka = strtok(command, " ");
    int args_count = 0;

    while (stroka != NULL && args_count < MAX_ARGS_COUNT - 1) {
        args[args_count++] = stroka;
        stroka = strtok(NULL, " ");
    }
    args[args_count] = NULL;

    if (args_count == 0) {
        return;
    }

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    pid_t child_pid = fork();
    if (child_pid < 0) {
        perror("fork error");
        exit(1);
    }

    if (child_pid == 0) {
        execvp(args[0], args);
        perror("exec error"); // Вывод ошибки, если execvp не сработал
        exit(1);
    } else {
        wait(NULL);
    }
}
