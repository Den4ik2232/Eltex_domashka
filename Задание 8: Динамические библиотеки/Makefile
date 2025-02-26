CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC
LDFLAGS = -shared

SRC_LIB = minus.c plus.c multiplication.c read_two_number.c division.c
OBJ_LIB = $(SRC_LIB:.c=.o)
LIB_NAME = libcalculator.so

SRC_MAIN = main.c
OBJ_MAIN = $(SRC_MAIN:.c=.o)
EXEC = calculator

all: $(LIB_NAME) $(EXEC)

$(LIB_NAME): $(OBJ_LIB)
	$(CC) $(LDFLAGS) -o $(LIB_NAME) $(OBJ_LIB)

$(EXEC): $(OBJ_MAIN) $(LIB_NAME)
	$(CC) $(OBJ_MAIN) -o $(EXEC) -L. -lcalculator -Wl,-rpath,.

%.o: %.c calculator.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_LIB) $(OBJ_MAIN)

fclean: clean
	rm -f $(EXEC) $(LIB_NAME)

re: fclean all

