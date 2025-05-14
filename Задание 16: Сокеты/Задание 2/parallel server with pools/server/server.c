#include "server.h"
#define SOCKET_PATH "./server_socket"
#define THREAD_POOL_SIZE 5


int client_fds[THREAD_POOL_SIZE] = {0};  // 0 - слот свободен
pthread_mutex_t fd_mutex = PTHREAD_MUTEX_INITIALIZER;

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

	pthread_t threads[THREAD_POOL_SIZE];
	for (int i = 0; i < THREAD_POOL_SIZE; i++) {
		int *arg = malloc(sizeof(int));
		*arg = i;
		if (pthread_create(&threads[i], NULL, thread_server, arg) != 0) {
			perror("pthread_create");
			exit(1);
		}
	}

	socklen_t client_len = sizeof(client);

	while (1) {
		int fd_client = accept(fd, (struct sockaddr *) &client, &client_len);
		if (fd_client < 0) {
			perror("accept");
			continue;
		}

		int assigned = 0;
		while (!assigned) {
			pthread_mutex_lock(&fd_mutex);
			for (int i = 0; i < THREAD_POOL_SIZE; i++) {
				if (client_fds[i] == 0) {
					client_fds[i] = fd_client;
					assigned = 1;
					break;
				}
			}
			pthread_mutex_unlock(&fd_mutex);

			if (!assigned) {
				usleep(10000); 
			}
		}
	}
}

void *thread_server(void *args) {
	int index = *(int *)args;
	free(args);

	while (1) {
		pthread_mutex_lock(&fd_mutex);
		int fd_client = client_fds[index];
		pthread_mutex_unlock(&fd_mutex);

		if (fd_client == 0) {
			usleep(10000);
			continue;
		}

		char buf[128] = {0};
		ssize_t n = recv(fd_client, buf, sizeof(buf), 0);
		if (n > 0) {
			printf("Thread %d received: %s\n", index, buf);

			time_t mytime = time(NULL);
			struct tm *now = localtime(&mytime);
			snprintf(buf, sizeof(buf), "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
			send(fd_client, buf, strlen(buf) + 1, 0);
			printf("Thread %d sent time to client\n", index);
		}

		close(fd_client);

		pthread_mutex_lock(&fd_mutex);
		client_fds[index] = 0; 
		pthread_mutex_unlock(&fd_mutex);
	}
	return NULL;
}

