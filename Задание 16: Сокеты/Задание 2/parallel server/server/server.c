#include "server.h"
#define SOCKET_PATH "./server_socket"

struct thread_args {
	int fd_client;
};

void *thread_server(void *args);

void run() {
	struct sockaddr_un serv, client;
	int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");
		exit(1);
	}

	unlink(SOCKET_PATH);

	serv.sun_family = AF_LOCAL;
	strncpy(serv.sun_path, SOCKET_PATH, sizeof(serv.sun_path) - 1);

	if (bind(fd, (struct sockaddr *) &serv, sizeof(serv)) < 0) {
		perror("bind");
		close(fd);
		exit(1);
	}

	if (listen(fd, 10) < 0) {
		perror("listen");
		close(fd);
		exit(1);
	}

	printf("Server is running on %s\n", SOCKET_PATH);

	socklen_t client_len = sizeof(client);

	while (1) {
		int fd_client = accept(fd, (struct sockaddr *) &client, &client_len);
		if (fd_client < 0) {
			perror("accept");
			continue;
		}

		struct thread_args *args = malloc(sizeof(struct thread_args));
		if (!args) {
			perror("malloc");
			close(fd_client);
			continue;
		}

		args->fd_client = fd_client;

		pthread_t thread;
		if (pthread_create(&thread, NULL, thread_server, (void *)args) != 0) {
			perror("pthread_create");
			close(fd_client);
			free(args);
			continue;
		}

		pthread_detach(thread);
	}
}

void *thread_server(void *args) {
	struct thread_args *data = (struct thread_args *) args;
	int fd_client = data->fd_client;
	free(data);

	char buf[128] = {0};

	ssize_t n = recv(fd_client, buf, sizeof(buf), 0);
	if (n <= 0) {
		close(fd_client);
		return NULL;
	}

	printf("Received: %s\n", buf);

	time_t mytime = time(NULL);
	struct tm *now = localtime(&mytime);
	snprintf(buf, sizeof(buf), "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
	send(fd_client, buf, strlen(buf) + 1, 0);
	printf("Server send time to client!\n");
	recv(fd_client, buf, sizeof(buf), 0);

	close(fd_client);
	return NULL;
}
