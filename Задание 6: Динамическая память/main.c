#include "abonents.h"

int main() {
    abonent* abonents = NULL;
    int choice;
    
    do {
        printf(
            "1) Добавить абонента\n"
            "2) Удалить абонента\n"
            "3) Поиск абонентов по имени\n"
            "4) Вывод всех записей\n"
            "5) Выход\n"
        );
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n' && getchar() != EOF);
            continue;
        }
        switch (choice) {
            case 1:
                add_abonent(&abonents);
                break;
            case 2:
                delete_abonent(&abonents);
                break;
            case 3:
                find_abonent(abonents);
                break;
            case 4:
                print_abonents(abonents);
                break;
            case 5:
                printf("Очистка памяти\n");
                delete_all(&abonents);
                break;
            default:
                printf("Ошибка! Неверное значение пункта меню.\n");
                break;
        }
    } while (choice != 5);
    return 0;
}

