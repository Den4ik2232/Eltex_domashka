#include "message_chat.h"

ChatData *chat_data = NULL;
sem_t *mutex = NULL, *sem_msg = NULL, *sem_update = NULL;

void *update_loop(void *arg) {
    while (1) {
        sem_wait(sem_msg);
        sem_post(sem_update); // notify clients of new message
    }
    return NULL;
}

void start() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(ChatData));
    chat_data = mmap(0, sizeof(ChatData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    memset(chat_data, 0, sizeof(ChatData));

    mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);
    sem_msg = sem_open(SEM_MSG, O_CREAT, 0666, 0);
    sem_update = sem_open(SEM_UPDATE, O_CREAT, 0666, 0);

    pthread_t updater;
    pthread_create(&updater, NULL, update_loop, NULL);

    printf("Server started. Waiting for clients...\n");
    pthread_join(updater, NULL);

    sem_close(mutex); sem_close(sem_msg); sem_close(sem_update);
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_MUTEX); sem_unlink(SEM_MSG); sem_unlink(SEM_UPDATE);
}

