#ifndef ABONENTS_H
#define ABONENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
    struct abonent* next;
} abonent;

void delete_all(abonent** head);
void input(char* inp, const char* text);
void add_abonent(abonent** head);
void delete_abonent(abonent** head);
void find_abonent(abonent* head);
void print_abonents(abonent* head);

#endif  // ABONENTS_H
