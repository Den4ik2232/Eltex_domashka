#include<stdio.h>

struct abonent {
char name[10];
char second_name[10];
char tel[10];
};

typedef struct abonent abonent;

void print_name(abonent *ukaz);
void print_second_name(abonent *ukaz);
void print_tel(abonent *ukaz);
void add_abonent(abonent *ukaz, char name[10], char second_name[10], char tel[10]);
void find_abonent(abonent *ukaz, char name[10]);
void delete_abonent(abonent *ukaz, char name[10], char second_name[10], char tel[10]);
void print_all(abonent *ukaz);

int main(void){
	abonent abonents[100] = {0};
	int n;
	int count_abonents = 0;
	printf("Выберите действие: \n1) Добавить абонента \n2) Удалить абонента \n3) Поиск абонентов по имени \n4) Вывод всех записей \n5) Выход\n");
	scanf("%d", &n);
	while(n != 5){
		if(n == 1){
			if(count_abonents < 100){
			char name[10] = {0}, second_name[10] = {0}, tel[10] = {10};
			while(getchar() != '\n');
			printf("Введите имя абонента(не более 10 символов): ");
			for(int i = 0; i <= 10; i++){
				char a = getchar();
				if(a != '\n') name[i] = a;
				else break;}
			printf("Введите фамилию абонента(не более 10 символов): ");
			for(int i = 0; i <= 10; i++){
				char a = getchar();
				if(a != '\n') second_name[i] = a;
				else break;}
			printf("Введите телефон абонента(не более 10 символов): ");
			for(int i = 0; i <= 10; i++){
				char a = getchar();
				if(a != '\n') tel[i] = a;
				else break;}
			add_abonent(abonents, name, second_name, tel);
			count_abonents++;}
			else printf("Больше нет места!\n");
		}
		if(n == 2){
			if(count_abonents > 0){
			char name[10] = {0}, second_name[10] = {0}, tel[10] = {10};
			while(getchar() != '\n');
			printf("Введите имя абонента(не более 10 символов): ");
			for(int i = 0; i <= 10; i++){
				char a = getchar();
				if(a != '\n') name[i] = a;
				else break;}
			printf("Введите фамилию абонента(не более 10 символов): ");
			for(int i = 0; i <= 10; i++){
				char a = getchar();
				if(a != '\n') second_name[i] = a;
				else break;}
			printf("Введите телефон абонента(не более 10 символов): ");
			for(int i = 0; i <= 10; i++){
				char a = getchar();
				if(a != '\n') tel[i] = a;
				else break;}
			delete_abonent(abonents, name, second_name, tel);
			count_abonents--;}
			else printf("Абонентов не найдено!\n");
		}
		if(n == 3){
			char name[10] = {0};
			while(getchar() != '\n');
			printf("Введите имя абонента(не более 10 символов): ");
			for(int i = 0; i < 10; i++){
				char a = getchar();
				if(a != '\n') name[i] = a;
				else break;}
			find_abonent(abonents, name);
		}
		if(n == 4){
			print_all(abonents);
			printf("Найдено %d абонентов\n", count_abonents);}
		if(n > 5 || n <= 0) printf("Такой команды нет!\n");
		printf("Выберите действие: \n1) Добавить абонента \n2) Удалить абонента \n3) Поиск абонентов по имени \n4) Вывод всех записей \n5) Выход\n");
		scanf("%d", &n);
		}
}

void print_name(abonent *ukaz){
	printf("Имя: ");
	for(int i = 0; i < 10; i++){
		printf("%c", ukaz->name[i]);}
}

void print_second_name(abonent *ukaz){
	printf("Фамилия: ");
	for(int i = 0; i < 10; i++){
		printf("%c", ukaz->second_name[i]);}
}

void print_tel(abonent *ukaz){
	printf("Номер телефона: ");
	for(int i = 0; i < 10; i++){
		printf("%c", ukaz->tel[i]);}
}

void add_abonent(abonent *ukaz, char name[10], char second_name[10], char tel[10]){
	abonent *ukaz1 = ukaz;
	while(ukaz1->name[0] != 0) ukaz1++;
	for(int l = 0; l < 10; l++){
		ukaz1->name[l] = 0;
		ukaz1->second_name[l] = 0;
		ukaz1->tel[l] = 0;}
	for(int i = 0; i < 10; i++){
		ukaz1->name[i] = name[i];
		ukaz1->second_name[i] = second_name[i];
		ukaz1->tel[i] = tel[i];}
}

void find_abonent(abonent *ukaz, char name[10]){
	abonent *ukaz1 = ukaz;
	int count = 0;
	for(int i = 0; i < 100; i++){
		int j = 0;
		while(ukaz1->name[j] == name[j] && j < 10) j++;
		if(j == 10){
			print_name(ukaz1);
			printf("\n");
			print_second_name(ukaz1);
			printf("\n");
			print_tel(ukaz1);
			printf("\n");
			count++;}
		ukaz1++;}
	printf("Найдено %d абонентов!\n", count);
}

void delete_abonent(abonent *ukaz, char name[10], char second_name[10], char tel[10]){
	abonent *ukaz1 = ukaz;
	char flag = 0;
	for(int i = 0; i < 100; i++){
		int j = 0;
		while(ukaz1->name[j] == name[j] && ukaz1->tel[j] == tel[j] && ukaz1->second_name[j] == second_name[j] && j < 10) j++;
		if(j == 10){
			for(int l = 0; l < 10; l++){
				ukaz1->name[l] = 0;
				ukaz1->second_name[l] = 0;
				ukaz1->tel[l] = 0;
				flag = 1;}
			break;}
		ukaz1++;}
	if(flag) printf("Абонент удален!");
	else printf("Абонент не найден!");
}

void print_all(abonent *ukaz){
abonent *ukaz1 = ukaz;
for(int i = 0; i < 100; i++){
	if(ukaz1->name[0] != 0){
		print_name(ukaz1);
		printf("\n");
		print_second_name(ukaz1);
		printf("\n");
		print_tel(ukaz1);
		printf("\n");}
	ukaz1++;}
}

