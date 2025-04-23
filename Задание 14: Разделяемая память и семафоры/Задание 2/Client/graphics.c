#include "graphics.h"
#include <ncurses.h>
#include <string.h>

WINDOW *msg_win, *input_win, *user_win;

void init_graphics() {
    initscr(); cbreak(); noecho(); curs_set(1);
    int h = LINES - 3, w = COLS - 20;
    msg_win = newwin(h, w, 0, 0);
    scrollok(msg_win, 1);
    input_win = newwin(3, w, h, 0);
    user_win = newwin(LINES, 20, 0, w);
    wborder(user_win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(user_win);
}

void close_graphics() {
    delwin(msg_win); delwin(input_win); delwin(user_win);
    endwin();
}

void draw_message(const char *sender, const char *msg) {
    wprintw(msg_win, "%s: %s\n", sender, msg);
    wrefresh(msg_win);
}

void get_input(char *buffer) {
    werase(input_win); wborder(input_win, '|', '|', '-', '-', '+', '+', '+', '+');
    wmove(input_win, 1, 2); wrefresh(input_win);
    wgetnstr(input_win, buffer, 128);
}

void draw_users(const char names[][32], const int connected[]) {
    werase(user_win); wborder(user_win, '|', '|', '-', '-', '+', '+', '+', '+');
    int y = 1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (connected[i]) {
            mvwprintw(user_win, y++, 2, "%s", names[i]);
        }
    }
    wrefresh(user_win);
}

