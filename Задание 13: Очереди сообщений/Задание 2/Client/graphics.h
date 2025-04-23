#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>
#include <string.h>

void init_graphics();
void draw_message(const char *msg);
void get_input(char *buffer);
void close_graphics();
void update_user_list(const char *user_list);

#endif // GRAPHICS_H
