CC = gcc
CFLAGS = -Wall

# Исходники
CLIENT_SRC = client/main.c client/client.c
SERVER_SRC = server/main.c server/server.c

# Цели
CLIENT_BIN = client_prog
SERVER_BIN = server_prog

all: $(CLIENT_BIN) $(SERVER_BIN)

$(CLIENT_BIN): $(CLIENT_SRC) 
	$(CC) $(CFLAGS) -o $@ $(CLIENT_SRC)

$(SERVER_BIN): $(SERVER_SRC) 
	$(CC) $(CFLAGS) -o $@ $(SERVER_SRC)

clean:
	rm -f $(CLIENT_BIN) $(SERVER_BIN)
