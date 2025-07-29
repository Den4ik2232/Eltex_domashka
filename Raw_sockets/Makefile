CC=gcc
CFLAGS=-Wall -Wextra -O2

all: server_prog client_prog

server_prog: server/server.c server/main.c
	$(CC) $(CFLAGS) -o server_prog server/server.c server/main.c

client_prog: client/client.c client/main.c
	$(CC) $(CFLAGS) -o client_prog client/client.c client/main.c

clean:
	rm -f server_prog client_prog
