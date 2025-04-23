#include "message_chat.h"
#include "graphics.h"

ChatData *chat_data = NULL;
sem_t *mutex = NULL, *sem_msg = NULL, *sem_update = NULL;
char username[MAX_NAME_LEN];
int client_index = -1;

void *receiver_thread(void *arg) {
    int prev_count = 0;
    while (1) {
        sem_wait(sem_update);
        sem_wait(mutex);
        for (int i = prev_count; i < chat_data->message_count; i++)
            draw_message(chat_data->messages[i].sender, chat_data->messages[i].content);
        prev_count = chat_data->message_count;
        draw_users((const char (*)[MAX_NAME_LEN])chat_data->names, chat_data->connected);
        sem_post(mutex);
    }
    return NULL;
}

void run() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    chat_data = mmap(0, sizeof(ChatData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    mutex = sem_open(SEM_MUTEX, 0);
    sem_msg = sem_open(SEM_MSG, 0);
    sem_update = sem_open(SEM_UPDATE, 0);

    printf("Enter name: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    sem_wait(mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (!chat_data->connected[i]) {
            client_index = i;
            strncpy(chat_data->names[i], username, MAX_NAME_LEN);
            chat_data->connected[i] = 1;
            break;
        }
    }
    sem_post(mutex);

    init_graphics();
    pthread_t thread;
    pthread_create(&thread, NULL, receiver_thread, NULL);

    for (int i = 0; i < chat_data->message_count; i++)
        draw_message(chat_data->messages[i].sender, chat_data->messages[i].content);
    draw_users((const char (*)[MAX_NAME_LEN])chat_data->names, chat_data->connected);

    while (1) {
        char input[MAX_MSG_LEN];
        get_input(input);
        if (strcmp(input, "/exit") == 0) break;

        sem_wait(mutex);
        if (chat_data->message_count < MAX_MESSAGES) {
            strncpy(chat_data->messages[chat_data->message_count].sender, username, MAX_NAME_LEN);
            strncpy(chat_data->messages[chat_data->message_count].content, input, MAX_MSG_LEN);
            chat_data->message_count++;
        }
        sem_post(mutex);
        sem_post(sem_msg);
    }

    sem_wait(mutex);
    chat_data->connected[client_index] = 0;
    sem_post(mutex);

    close_graphics();
    sem_close(mutex); sem_close(sem_msg); sem_close(sem_update);
}

