# Компилятор и флаги
CC = gcc

# Директории
SERVER_DIR = prog1
CLIENT_DIR = prog2

# Исходные файлы
SERVER_SRC = $(SERVER_DIR)/main.c $(SERVER_DIR)/sign.c
CLIENT_SRC = $(CLIENT_DIR)/main.c $(CLIENT_DIR)/sign.c

# Объектные файлы
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Исполняемые файлы
SERVER_BIN = program1
CLIENT_BIN = program2

# Правило сборки всех целей
all: $(SERVER_BIN) $(CLIENT_BIN)

# Создание сервера
$(SERVER_BIN): $(SERVER_OBJ)
	$(CC) $^ -o $@

# Создание клиента
$(CLIENT_BIN): $(CLIENT_OBJ)
	$(CC) $^ -o $@

# Компиляция объектных файлов
%.o: %.c
	$(CC) -c $< -o $@

# Очистка объектных и исполняемых файлов
clean:
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ) $(SERVER_BIN) $(CLIENT_BIN)

# Полная очистка и пересборка
fclean: clean

re: fclean all
