CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses

SRC = file_manager.c main1.c
OBJ = $(SRC:.c=.o)
EXEC = program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all
