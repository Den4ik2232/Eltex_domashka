#include "abonents.h"

void delete_all(abonent** head) {
    abonent* current = *head;
    while (current != NULL) {
        abonent* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void input(char* inp, const char* text) {
    while (1) {
        printf("%s", text);
        if (scanf("%10s", inp) == 1) {
            if (strlen(inp) == 10) {
                int c = getchar();
                if (c != '\n' && c != EOF) {
                    printf("Введено больше 10 символов. Попробуйте снова.\n");
                    while (getchar() != '\n' && getchar() != EOF);
                    continue;
                }
            }
            break;
        } else {
            printf("Ошибка!!! Попробуйте снова.\n");
            while (getchar() != '\n' && getchar() != EOF);
        }
    }
}

void add_abonent(abonent** head) {
    abonent* new_abonent = (abonent*)malloc(sizeof(abonent));
    if (!new_abonent) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    input(new_abonent->name, "Введите имя (не более 10 символов): ");
    input(new_abonent->second_name, "Введите фамилию (не более 10 символов): ");
    input(new_abonent->tel, "Введите номер телефона (не более 10 символов): ");
    new_abonent->next = *head;
    *head = new_abonent;
}

void delete_abonent(abonent** head) {
    char name[10], second_name[10];
    input(name, "Введите имя (не более 10 символов): ");
    input(second_name, "Введите фамилию (не более 10 символов): ");
    
    abonent* current = *head;
    abonent* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->second_name, second_name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Абонент удален.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Абонента с таким именем не найдено.\n");
}

void find_abonent(abonent* head) {
    char name[10], second_name[10];
    input(name, "Введите имя (не более 10 символов): ");
    input(second_name, "Введите фамилию (не более 10 символов): ");
    
    abonent* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->second_name, second_name) == 0) {
            printf("Имя: %s, Фамилия: %s, Телефон: %s\n", current->name, current->second_name, current->tel);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("Абоненты с таким именем не найдены.\n");
    }
}

void print_abonents(abonent* head) {
    abonent* current = head;
    while (current != NULL) {
        printf("Имя: %s, Фамилия: %s, Телефон: %s\n", current->name, current->second_name, current->tel);
        current = current->next;
    }
}

