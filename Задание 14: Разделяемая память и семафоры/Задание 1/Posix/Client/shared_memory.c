#include"shared_memory.h"

void run(){
    int fd_shm = shm_open("/shared_memory", O_RDWR, 0660);
    if (fd_shm == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(fd_shm, sizeof(struct msg)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    struct msg* message = mmap(NULL, sizeof(struct msg),
                               PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (message == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    strcpy(message->msg_shm[1], "Hello!");

    while (1) {
        if (message->msg_shm[0][0]) {
            printf("Received: %s\n", message->msg_shm[0]);
            break;
        }
    }

    shm_unlink("/shared_memory");
}
