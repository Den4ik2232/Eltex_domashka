CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c WRFile.c
OBJ = $(SRC:.c=.o)
EXEC = program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c WRFile.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) *.txt

fclean: clean
	rm -f $(EXEC)

re: fclean all
