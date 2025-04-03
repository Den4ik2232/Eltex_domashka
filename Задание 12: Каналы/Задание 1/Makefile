C=gcc
CFLAGS=-Wall -Wextra
OBJ=pipes.o main.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

CreateProcess.o: pipes.c pipes.h
	$(CC) $(CFLAGS) -c pipes.c

main.o: main.c pipes.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o program
