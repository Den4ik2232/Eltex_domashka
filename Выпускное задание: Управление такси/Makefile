CC = gcc
CFLAGS = -Wall

SRC = main.c taxi.c
OBJ = $(SRC:.c=.o)
EXEC = taxi_simulation

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c taxi.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

