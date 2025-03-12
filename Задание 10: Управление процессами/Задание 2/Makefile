CC=gcc
CFLAGS=-Wall -Wextra -std=c11
OBJ=create_processes.o main.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

create_processes.o: create_processes.c create_processes.h
	$(CC) $(CFLAGS) -c create_processes.c

main.o: main.c create_processes.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o program
