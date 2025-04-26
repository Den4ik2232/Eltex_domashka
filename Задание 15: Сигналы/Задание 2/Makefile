C=gcc
CFLAGS=-Wall 
OBJ=sign.o main.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

sign.o: sign.c sign.h
	$(CC) $(CFLAGS) -c sign.c

main.o: main.c sign.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o program
