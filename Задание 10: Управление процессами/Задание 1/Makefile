C=gcc
CFLAGS=-Wall -Wextra -std=c11
OBJ=CreateProcess.o main.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

CreateProcess.o: CreateProcess.c CreateProcess.h
	$(CC) $(CFLAGS) -c CreateProcess.c

main.o: main.c CreateProcess.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o program
