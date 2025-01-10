#include <stdio.h>

int main() {
    int n1, n2;
    printf("Введите количество символов в строке: ");
    scanf("%d", &n1);
    char stroka[n1 + 1]; 
    printf("Введите строку: ");
    while (getchar() != '\n'); 
    for (int i = 0; i < n1; i++) {
        scanf("%c", &stroka[i]);
    }
    stroka[n1] = '\0';

    printf("Введите количество символов в подстроке: ");
    scanf("%d", &n2);
    char podstroka[n2 + 1];
    printf("Введите подстроку: ");
    while (getchar() != '\n');
    for (int i = 0; i < n2; i++) {
        scanf("%c", &podstroka[i]);
    }
    podstroka[n2] = '\0';

    char flag = 0;
    char *result = NULL;

    for (char *ukaz = stroka; *ukaz != '\0'; ukaz++) {
        char *ukaz1 = ukaz;
        char *ukaz2 = podstroka;
        while (*ukaz1 == *ukaz2 && *ukaz2 != '\0') {
            ukaz1++;
            ukaz2++;
        }
        if (*ukaz2 == '\0') { 
            flag = 1;
            result = ukaz;
            break;
        }
    }

    if (flag) {
        printf("Подстрока найдена! Индекс начала: %ld\n", result - stroka);
    } else {
        printf("Подстрока не найдена!\n");
    }

    return 0;
}
