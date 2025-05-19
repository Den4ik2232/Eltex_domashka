CC = gcc
CFLAGS = -Wall

all: serv client

serv: server.c
	$(CC) $(CFLAGS) -o serv server.c

client: client.c
	$(CC) $(CFLAGS) -o client client.c

clean:
	rm -f serv client
