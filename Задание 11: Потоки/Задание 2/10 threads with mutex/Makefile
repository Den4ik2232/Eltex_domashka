C=gcc
CFLAGS=-Wall -Wextra -lpthread
OBJ=threads.o main.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

CreateProcess.o: threads.c threads.h
	$(CC) $(CFLAGS) -c threads.c

main.o: main.c threads.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o program
