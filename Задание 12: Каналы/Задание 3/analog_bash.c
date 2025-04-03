#include "analog_bash.h"

#define MAX_COMMANDS 10

void run_command(char *command) {
    char *commands[MAX_COMMANDS];
    char *args[MAX_ARGS_COUNT];
    int pipes[MAX_COMMANDS - 1][2];
    int cmd_count = 0;

    // Разбиваем команду по '|'
    char *cmd = strtok(command, "|");
    while (cmd != NULL && cmd_count < MAX_COMMANDS) {
        commands[cmd_count++] = cmd;
        cmd = strtok(NULL, "|");
    }

    if(strcmp(commands[0], "exit") == 0) exit(0);

    for (int i = 0; i < cmd_count; i++) {
        // Создаем пайп (если не последняя команда)
        if (i < cmd_count - 1) {
            if (pipe(pipes[i]) < 0) {
                perror("pipe error");
                exit(1);
            }
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork error");
            exit(1);
        }

        if (pid == 0) {  // Дочерний процесс
            if (i > 0) {  // Если не первая команда, перенаправляем stdin
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            if (i < cmd_count - 1) {  // Если не последняя команда, перенаправляем stdout
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            // Закрываем все пайпы в дочернем процессе
            for (int j = 0; j < cmd_count - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Разбиваем команду на аргументы
            char *arg = strtok(commands[i], " ");
            int arg_count = 0;
            while (arg != NULL && arg_count < MAX_ARGS_COUNT - 1) {
                args[arg_count++] = arg;
                arg = strtok(NULL, " ");
            }
            args[arg_count] = NULL;

            // Выполняем команду
            execvp(args[0], args);
            perror("exec error");
            exit(1);
        }
    }

    // Закрываем все пайпы в родительском процессе
    for (int i = 0; i < cmd_count - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Ждем завершения всех процессов
    for (int i = 0; i < cmd_count; i++) {
        wait(NULL);
    }
}
