#include "abonents.h"

#include<malloc.h>
#include<string.h>

void realloc_memory(abonent** abonents, int new_size) {
    abonent* ukaz = realloc(*abonents, new_size * sizeof(abonent));
    if (ukaz != NULL || new_size == 0) { 
        *abonents = ukaz;
    } else {
        printf("Ошибка при выделении памяти\n");
        delete_all(abonents);
    }
}


void delete_all(abonent** abonents){
	free(*abonents);
	*abonents = NULL;
}

void input(char* inp, const char* text){
while (1) {
    printf("%s", text);
    if (scanf("%10s", inp) == 1) {
      if (strlen(inp) == 10) {
        int c = getchar();
        if (c != '\n' && c != EOF) {
          printf("Введено больше 10 символов. Попробуйте снова.\n");
	  while (getchar() != '\n' && getchar() != EOF);//очистка буфера ввода
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


void add_abonent(abonent** abonents, int* size) {
    realloc_memory(abonents, *size + 1);
    (*size)++; 
    input((*abonents)[*size - 1].name, "Введите имя(не более 10 символов): ");
    input((*abonents)[*size - 1].second_name, "Введите фамилию(не более 10 символов): ");
    input((*abonents)[*size - 1].tel, "Введите номер телефона(не более 10 символов): ");
}


void delete_abonent(abonent** abonents, int* size){
	char name[10], second_name[10];
  	input(name, "Введите имя(не более 10 символов): ");
  	input(second_name, "Введите фамилию(не более 10 символов): ");
  	int found = 0;
  	for (int i = 0; i < *size; i++) {
    		if (strcmp((*abonents)[i].name, name) == 0 &&
        		strcmp((*abonents)[i].second_name, second_name) == 0) {
      				for (int j = i; j < *size - 1; j++) {
        				(*abonents)[j] = (*abonents)[j + 1];
      				}
      			realloc_memory(abonents, *size - 1);
			(*size)--;
      			if (*abonents == NULL)
        			return;
      			printf("Абонент удален.\n");
      			found = 1;
    				}
 			 }
  if (!found) {
    printf("Абонента с таким именем не найдено.\n");
  }
}

void find_abonent(abonent* abonents, int size){
	char name[10], second_name[10];
        input(name, "Введите имя(не более 10 символов): ");
        input(second_name, "Введите фамилию(не более 10 символов): ");
	int found = 0;
 	 for (int i = 0; i < size; i++) {
    		if (strcmp(abonents[i].name, name) == 0 &&
        		strcmp(abonents[i].second_name, second_name) == 0) {
      			printf("Имя: %s, Фамилия: %s, Телефон: %s\n", abonents[i].name,
             		abonents[i].second_name, abonents[i].tel);
      			found = 1;
   			 }
 		 }
  	if (!found) {
    		printf("Абоненты с таким именем не найдены.\n");
  		}
}

void print_abonents(abonent* abonents, int size){
	for(int i = 0; i < size; i++){
		printf("Имя: %s, Фамилия: %s, Телефон: %s\n", abonents[i].name, abonents[i].second_name, abonents[i].tel);
	}
}




