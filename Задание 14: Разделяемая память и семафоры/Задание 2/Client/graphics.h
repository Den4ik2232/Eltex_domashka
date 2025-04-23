#ifndef GRAPHICS_H
#define GRAPHICS_H

#define MAX_CLIENTS 5
#define MAX_MESSAGES 128
#define MAX_MSG_LEN 128
#define MAX_NAME_LEN 32

void init_graphics();
void close_graphics();
void draw_message(const char *sender, const char *msg);
void get_input(char *buffer);
void draw_users(const char names[][32], const int connected[]);

#endif
