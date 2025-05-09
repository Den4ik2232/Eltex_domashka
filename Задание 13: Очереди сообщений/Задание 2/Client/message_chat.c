#include "message_chat.h"
#include "graphics.h"

char name[32];
char client_queue[64];
mqd_t client_q;
mqd_t server_q;

void *receive_messages(void *arg) {
    char buffer[MAX_MSG_SIZE];
    while (1) {
        ssize_t bytes_read = mq_receive(client_q, buffer, MAX_MSG_SIZE, NULL);
        if (bytes_read > 0) {
            if (strncmp(buffer, "USERS:", 6) == 0) {
                update_user_list(buffer + 6);
            } else {
                draw_message(buffer);
            }
        }
    }
    return NULL;
}

void run() {
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    snprintf(client_queue, sizeof(client_queue), "/client_%d", getpid());

    struct mq_attr attr = {0};
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;

    mq_unlink(client_queue);
    client_q = mq_open(client_queue, O_CREAT | O_RDONLY, 0666, &attr);
    if (client_q == -1) {
        perror("Client mq_open");
        exit(1);
    }

    server_q = mq_open(SERVER_QUEUE, O_WRONLY);
    if (server_q == -1) {
        perror("Cannot connect to server");
        exit(1);
    }

    char join_msg[MAX_MSG_SIZE];
    snprintf(join_msg, sizeof(join_msg), "JOIN:%s:%s", name, client_queue);
    mq_send(server_q, join_msg, strlen(join_msg) + 1, 0);

    init_graphics();
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, NULL);

    char text[512];
    while (1) {
        get_input(text);
        if (strcmp(text, "/exit") == 0) {
            char exit_msg[MAX_MSG_SIZE];
            snprintf(exit_msg, sizeof(exit_msg), "EXIT:%s:%s", name, client_queue);
            mq_send(server_q, exit_msg, strlen(exit_msg) + 1, 0);
            break;
        }

        char full_msg[MAX_MSG_SIZE];
        snprintf(full_msg, sizeof(full_msg), "MSG:%s: %s", name, text);
        mq_send(server_q, full_msg, strlen(full_msg) + 1, 0);
    }

    pthread_cancel(recv_thread);
    pthread_join(recv_thread, NULL);
    mq_close(client_q);
    mq_unlink(client_queue);
    mq_close(server_q);
    close_graphics();
}

