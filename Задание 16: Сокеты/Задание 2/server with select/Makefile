# Компилятор и флаги
CC = gcc
CFLAGS = -Wall

# Директории
SERVER_DIR = server
CLIENT_DIR = client

# Исходные файлы
SERVER_SRC = $(SERVER_DIR)/main.c $(SERVER_DIR)/server.c
CLIENT_SRC = $(CLIENT_DIR)/client.c

# Объектные файлы
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Исполняемые файлы
SERVER_BIN = prog_server
CLIENT_BIN = prog_client

# Правило сборки всех целей
all: $(SERVER_BIN) $(CLIENT_BIN)

# Создание сервера
$(SERVER_BIN): $(SERVER_OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

# Создание клиента
$(CLIENT_BIN): $(CLIENT_OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

# Компиляция объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка объектных и исполняемых файлов
clean:
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ) $(SERVER_BIN) $(CLIENT_BIN) server_socket

# Полная очистка и пересборка
fclean: clean

re: fclean all


