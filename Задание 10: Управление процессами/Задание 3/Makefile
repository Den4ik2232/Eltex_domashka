CC=gcc
CFLAGS=-Wall -Wextra -std=c11
OBJ=analog_bash.o main.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

analog_bash.o: analog_bash.c analog_bash.h
	$(CC) $(CFLAGS) -c analog_bash.c

main.o: main.c analog_bash.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o program
