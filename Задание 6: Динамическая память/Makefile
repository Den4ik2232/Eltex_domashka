CC=gcc
CFLAGS=-Wall -Wextra -std=c11
OBJ=abonents.o main.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

abonents.o: abonents.c abonents.h
	$(CC) $(CFLAGS) -c abonents.c

main.o: main.c abonents.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o program

