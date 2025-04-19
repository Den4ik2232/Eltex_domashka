# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Директории
SERVER_DIR = Server
CLIENT_DIR = Client

# Исходные файлы
SERVER_SRC = $(SERVER_DIR)/main.c $(SERVER_DIR)/msg_queue.c
CLIENT_SRC = $(CLIENT_DIR)/main.c $(CLIENT_DIR)/msg_queue.c

# Объектные файлы
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Исполняемые файлы
SERVER_BIN = server
CLIENT_BIN = client

# Правило сборки всех целей
all: $(SERVER_BIN) $(CLIENT_BIN)

# Создание сервера
$(SERVER_BIN): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Создание клиента
$(CLIENT_BIN): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Компиляция объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка объектных и исполняемых файлов
clean:
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ) $(SERVER_BIN) $(CLIENT_BIN)

# Полная очистка и пересборка
fclean: clean

re: fclean all
