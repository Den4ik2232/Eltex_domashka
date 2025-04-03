#ifndef ANALOG_BASH_H
#define ANALOG_BASH_H

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_COUNT 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void run_command(char *command);

#endif //ANALOG_BASH_H

