#include "server.h"
#define SOCKET_PATH "./server_socket"
#define THREAD_POOL_SIZE 5
#define QUEUE_SIZE 100

int queue[QUEUE_SIZE];
int front = 0, rear = 0, count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void enqueue(int fd) {
	pthread_mutex_lock(&mutex);
	while (count == QUEUE_SIZE) pthread_cond_wait(&cond, &mutex);
	queue[rear] = fd;
	rear = (rear + 1) % QUEUE_SIZE;
	count++;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
}

int dequeue() {
	pthread_mutex_lock(&mutex);
	while (count == 0) pthread_cond_wait(&cond, &mutex); 
	int fd = queue[front];
	front = (front + 1) % QUEUE_SIZE;
	count--;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	return fd;
}

void *thread_server(void *args) {
	while (1) {
		int fd_client = dequeue();

		char buf[128] = {0};
		ssize_t n = recv(fd_client, buf, sizeof(buf), 0);
		if (n <= 0) {
			close(fd_client);
			continue;
		}

		printf("Received: %s\n", buf);

		time_t mytime = time(NULL);
		struct tm *now = localtime(&mytime);
		snprintf(buf, sizeof(buf), "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
		send(fd_client, buf, strlen(buf) + 1, 0);
		printf("Server sent time to client!\n");

		recv(fd_client, buf, sizeof(buf), 0); 
		close(fd_client);
	}
	return NULL;
}

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
		if (pthread_create(&threads[i], NULL, thread_server, NULL) != 0) {
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
		enqueue(fd_client); 
	}
}
