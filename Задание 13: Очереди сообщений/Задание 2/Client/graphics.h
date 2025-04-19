#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>

void init_graphics();
void draw_message(const char *msg);
void draw_input(const char *input);
void draw_user_list(char users[][32], int count);
void get_input(char *buffer, int size);
void close_graphics();

#endif
