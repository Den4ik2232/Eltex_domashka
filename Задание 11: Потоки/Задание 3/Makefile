C=gcc
CFLAGS=-Wall -Wextra -lpthread
OBJ=life.o main.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

CreateProcess.o: life.c life.h
	$(CC) $(CFLAGS) -c threads.c

main.o: main.c life.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o program
