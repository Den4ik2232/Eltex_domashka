#ifndef ABONENTS_H
#define ABONENTS_H

#include<stdio.h>

typedef struct {
  char name[10];
  char second_name[10];
  char tel[10];
} abonent;

void realloc_memory(abonent** abonents, int new_size);
void delete_all(abonent** abonents);
void clear_input_buffer();
void input(char* input, const char* text);
void add_abonent(abonent** abonents, int* size);
void delete_abonent(abonent** abonents, int* size);
void find_abonent(abonent* abonents, int size);
void print_abonents(abonent* abonents, int size);

#endif  // ABONENTS_H
