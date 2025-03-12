#include"analog_bash.h"

int main() {
    char read_command[MAX_INPUT_SIZE];

    while (1) {
        printf("analog-bash-> ");
        if (fgets(read_command, MAX_INPUT_SIZE, stdin) == NULL) {
            break;
        }   
        read_command[strcspn(read_command, "\n")] = 0;
        run_command(read_command);
    }

    return 0;
}
