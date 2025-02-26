#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <curses.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <termios.h>
#include <time.h>

extern WINDOW *left_wnd, *right_wnd;

extern int left_file_count;
extern int right_file_count;

extern int right_file;
extern int left_file;

extern int start_row_right;
extern int left_row_right;

extern char right_path[256];

extern char left_path[256];

extern struct dirent **namelist_left;
extern struct dirent **namelist_right;

extern bool wnd_now;

void run();

void display_table(WINDOW *win, struct dirent **namelist, int file_count, int file, bool wnd, bool wnd_sel, int start_row);

void action(int choice);

void open_directory(int file, struct dirent **namelist);

void minus_str(char* str1);

void sig_winch();

#endif // FILE_MANAGER_H



