#include "graphics.h"

WINDOW *chat_win, *input_win, *user_win;

void init_graphics() {
    initscr();
    cbreak();
    noecho();
    curs_set(1);

    int height = LINES - 3;
    int width = COLS - 20;
    chat_win = newwin(height, width, 0, 0);
    scrollok(chat_win, TRUE);

    input_win = newwin(3, width, LINES - 3, 0);
    box(input_win, 0, 0);
    wrefresh(input_win);

    user_win = newwin(LINES, 20, 0, COLS - 20);
    box(user_win, 0, 0);
    mvwprintw(user_win, 0, 1, " Users ");
    wrefresh(user_win);

    wrefresh(chat_win);
}

void draw_message(const char *msg) {
    wprintw(chat_win, "%s\n", msg);
    wrefresh(chat_win);
}

void get_input(char *buffer) {
    werase(input_win);
    box(input_win, 0, 0);
    wmove(input_win, 1, 1);
    wrefresh(input_win);
    wgetnstr(input_win, buffer, 512);
}

void close_graphics() {
    delwin(chat_win);
    delwin(input_win);
    delwin(user_win);
    endwin();
}

void update_user_list(const char *user_list) {
    werase(user_win);
    box(user_win, 0, 0);
    mvwprintw(user_win, 0, 1, " Users ");
    int line = 1;
    char copy[256];
    strncpy(copy, user_list, sizeof(copy));
    char *token = strtok(copy, ",");
    while (token != NULL && line < LINES - 1) {
        mvwprintw(user_win, line++, 1, "%s", token);
        token = strtok(NULL, ",");
    }
    wrefresh(user_win);
}

