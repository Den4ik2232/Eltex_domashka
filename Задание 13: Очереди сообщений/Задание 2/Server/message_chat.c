#include "message_chat.h"

ClientInfo clients[MAX_CLIENTS];
mqd_t server_q;
int client_count = 0;
char message[MAX_COUNT_MESSAGE][MAX_LEN_MESSAGE];
int message_count = 0;

void send_to_all_clients(const char *msg) {
    for (int i = 0; i < client_count; ++i) {
        mqd_t client_q = mq_open(clients[i].queue_name, O_WRONLY);
        if (client_q != -1) {
            mq_send(client_q, msg, strlen(msg) + 1, 0);
            mq_close(client_q);
        }
    }
}

void send_user_list() {
    char user_list[MAX_LEN_MESSAGE] = "USERS:";
    for (int i = 0; i < client_count; i++) {
        strcat(user_list, clients[i].name);
        if (i != client_count - 1) strcat(user_list, ",");
    }
    send_to_all_clients(user_list);
}

void *listen_clients(void *arg) {
    char buffer[MAX_LEN_MESSAGE];
    while (1) {
        ssize_t bytes_read = mq_receive(server_q, buffer, MAX_LEN_MESSAGE, NULL);
        if (bytes_read > 0) {
            if (strncmp(buffer, "JOIN:", 5) == 0) {
                char name[32], queue_name[64];
                sscanf(buffer, "JOIN:%31[^:]:%63s", name, queue_name);
                if (client_count < MAX_CLIENTS) {
                    strncpy(clients[client_count].name, name, 32);
                    strncpy(clients[client_count].queue_name, queue_name, 64);
                    client_count++;

                    for (int i = 0; i < message_count; ++i) {
                        mqd_t client_q = mq_open(queue_name, O_WRONLY);
                        if (client_q != -1) {
                            mq_send(client_q, message[i], strlen(message[i]) + 1, 0);
                            mq_close(client_q);
                        }
                    }

                    char join_msg[MAX_LEN_MESSAGE];
                    snprintf(join_msg, MAX_LEN_MESSAGE, "SERVER: %s joined the chat", name);
                    strncpy(message[message_count++], join_msg, MAX_LEN_MESSAGE);
                    send_to_all_clients(join_msg);
                    send_user_list();
                }
            } else if (strncmp(buffer, "MSG:", 4) == 0) {
                if (message_count < MAX_COUNT_MESSAGE) {
                    strncpy(message[message_count++], buffer + 4, MAX_LEN_MESSAGE);
                }
                send_to_all_clients(buffer + 4);
            } else if (strncmp(buffer, "EXIT:", 5) == 0) {
                char name[32], queue_name[64];
                sscanf(buffer, "EXIT:%31[^:]:%63s", name, queue_name);
                del_client(name, queue_name);
                char exit_msg[MAX_LEN_MESSAGE];
                snprintf(exit_msg, MAX_LEN_MESSAGE, "SERVER: %s left the chat", name);
                strncpy(message[message_count++], exit_msg, MAX_LEN_MESSAGE);
                send_to_all_clients(exit_msg);
                send_user_list();
            }
        }
    }
    return NULL;
}

void del_client(char name[32], char queue_name[64]) {
    for (int i = 0; i < client_count; i++) {
        if (strncmp(clients[i].name, name, 32) == 0 && strncmp(clients[i].queue_name, queue_name, 64) == 0) {
            for (int j = i; j < client_count - 1; j++) {
                clients[j] = clients[j + 1];
            }
            client_count--;
            break;
        }
    }
}

void start() {
    struct mq_attr attr = {0};
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_LEN_MESSAGE;

    mq_unlink(SERVER_QUEUE);
    server_q = mq_open(SERVER_QUEUE, O_CREAT | O_RDONLY, 0666, &attr);
    if (server_q == -1) {
        perror("Server mq_open");
        exit(1);
    }

    printf("Server started. Waiting for clients...\n");

    pthread_t thread;
    pthread_create(&thread, NULL, listen_clients, NULL);
    pthread_join(thread, NULL);

    mq_close(server_q);
    mq_unlink(SERVER_QUEUE);
}
