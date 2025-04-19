#include "graphics.h"
#include <string.h>

WINDOW *msg_win, *input_win, *user_win;

void init_graphics() {
    initscr();
    cbreak();
    noecho();
    curs_set(1);

    int msg_height = LINES - 3;
    int input_height = 3;
    int user_width = 20;
    int msg_width = COLS - user_width;

    msg_win = newwin(msg_height, msg_width, 0, 0);
    scrollok(msg_win, TRUE);

    input_win = newwin(input_height, msg_width, msg_height, 0);

    user_win = newwin(LINES, user_width, 0, msg_width);

    box(user_win, 0, 0);
    wrefresh(user_win);
    wrefresh(msg_win);
    wrefresh(input_win);
}

void draw_message(const char *msg) {
    wprintw(msg_win, "%s\n", msg);
    wrefresh(msg_win);
}

void draw_input(const char *input) {
    werase(input_win);
    box(input_win, 0, 0);
    mvwprintw(input_win, 1, 1, "%s", input);
    wrefresh(input_win);
}

void draw_user_list(char users[][32], int count) {
    werase(user_win);
    box(user_win, 0, 0);
    mvwprintw(user_win, 0, 2, " Users ");
    for (int i = 0; i < count; ++i) {
        mvwprintw(user_win, i + 1, 2, "%s", users[i]);
    }
    wrefresh(user_win);
}

void get_input(char *buffer, int size) {
    int pos = 0;
    int ch;

    memset(buffer, 0, size);

    draw_input(buffer);
    keypad(input_win, TRUE);

    while ((ch = wgetch(input_win)) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (pos > 0) {
                buffer[--pos] = '\0';
            }
        } else if (pos < size - 2 && ch >= 32 && ch <= 126) {
            buffer[pos++] = (char)ch;
        }
        buffer[pos] = '\0';
        draw_input(buffer);
    }
}

void close_graphics() {
    delwin(msg_win);
    delwin(input_win);
    delwin(user_win);
    endwin();
}
