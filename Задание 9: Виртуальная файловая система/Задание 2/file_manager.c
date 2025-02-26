#include "file_manager.h"


WINDOW *left_wnd, *right_wnd;

int left_file_count;
int right_file_count;

struct dirent **namelist_left;
struct dirent **namelist_right;

int left_file = 1;
int right_file = 1;

int start_row_left = 1;
int start_row_right = 1;

char right_path[256] = "/";
char left_path[256] = "/";

bool wnd_now = false; //0 - left, 1 - right;

void sig_winch() {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char*)&size);
  resizeterm(size.ws_row, size.ws_col);

  wresize(left_wnd, size.ws_row, size.ws_col / 2);
  mvwin(left_wnd, 0, 0);
  box(left_wnd, 0, 0);
  display_table(left_wnd, namelist_left, left_file_count, left_file, wnd_now, 0, start_row_left);

  wresize(right_wnd, size.ws_row, size.ws_col / 2);
  mvwin(right_wnd, 0, size.ws_col / 2);
  box(right_wnd, 0, 0);
  display_table(right_wnd, namelist_right, right_file_count, right_file, wnd_now, 1, start_row_right);

  wrefresh(left_wnd);
  wrefresh(right_wnd);

  keypad(stdscr, TRUE);
  refresh();
}




void run(){
	initscr();
 	signal(SIGWINCH, sig_winch);
  	noecho();
  	curs_set(FALSE);
  	keypad(stdscr, TRUE);
  	start_color();
  	refresh();
  	init_pair(1, COLOR_GREEN, COLOR_BLACK);
  	init_pair(2, COLOR_RED, COLOR_BLACK);

  	int rows, cols;
  	getmaxyx(stdscr, rows, cols);

  	left_wnd = newwin(rows, cols / 2, 0, 0);
  	wattron(left_wnd, COLOR_PAIR(2));
  	wattron(stdscr, COLOR_PAIR(2));
  	box(left_wnd, 0, 0);

  	right_wnd = newwin(rows, cols / 2, 0, cols / 2);
  	wattron(right_wnd, COLOR_PAIR(2));
  	box(right_wnd, 0, 0);
	left_file_count = scandir(left_path, &namelist_left, NULL, alphasort);
	right_file_count = scandir(right_path, &namelist_right, NULL, alphasort);
	display_table(left_wnd, namelist_left, left_file_count, left_file, wnd_now, 0, start_row_left);
	display_table(right_wnd, namelist_right, right_file_count, right_file, wnd_now, 1, start_row_right);

	while(true){
		int choice = wgetch(stdscr);
		if (choice == 'q') break;
		else if(choice == KEY_RESIZE) sig_winch(1);
		else action(choice);
	}

	delwin(left_wnd);
	delwin(right_wnd);
	endwin();
}



void action(int choice){
	switch(choice){
		case '\t':
			wnd_now = !wnd_now;
			display_table(left_wnd, namelist_left, left_file_count, left_file, wnd_now, 0, start_row_left);
        		display_table(right_wnd, namelist_right, right_file_count, right_file, wnd_now, 1, start_row_right);
			break;
		case KEY_UP:
			if(wnd_now){
				if(right_file - 1 == start_row_right && start_row_right > 1) {
					start_row_right--; 
					right_file--; 
					display_table(right_wnd, namelist_right, right_file_count, right_file, wnd_now, 1, start_row_right);
				}
				else if(start_row_right == 1 && right_file == 1);
				else{
					right_file--;
					display_table(right_wnd, namelist_right, right_file_count, right_file, wnd_now, 1, start_row_right);
				}}
			else{
				if(left_file - 1 == start_row_left && start_row_left > 1){
					start_row_left--;
					left_file--;
					display_table(left_wnd, namelist_left, left_file_count, right_file, wnd_now, 0, start_row_left);
				
				}
				else if(start_row_left == 1 && right_file == 1);
				else{
					left_file--;
					display_table(left_wnd, namelist_left, left_file_count, left_file, wnd_now, 0, start_row_left);
				}
			}
			break;
		case KEY_DOWN:
			if(wnd_now){
				if(right_file == right_file_count - 1);
				else if(right_file < getmaxy(right_wnd) - 6){
					right_file++;
					display_table(right_wnd, namelist_right, right_file_count, right_file, wnd_now, 1, start_row_right);
				}
				else{
					start_row_right++;
					right_file++;
					display_table(right_wnd, namelist_right, right_file_count, right_file, wnd_now, 1, start_row_right);
				}
			}
			else{
				if(left_file == left_file_count - 1);
				else if(left_file < getmaxy(left_wnd) - 6){
					left_file++;
					display_table(left_wnd, namelist_left, left_file_count, left_file, wnd_now, 0, start_row_left);
				}
				else{
					start_row_left++;
					left_file++;
					display_table(left_wnd, namelist_left, left_file_count, left_file, wnd_now, 0, start_row_left);
				}
			}
			break;
		case '\n':
			if(wnd_now){
				open_directory(right_file, namelist_right);
				display_table(right_wnd, namelist_right, right_file_count, right_file, wnd_now, 1, start_row_right);
			}
			else {
				open_directory(left_file, namelist_left);
				display_table(left_wnd, namelist_left, left_file_count, left_file, wnd_now, 0, start_row_right);
			}
			break;			
	}
}



void minus_str(char* str1){
        for(int i = strlen(str1); i > 0; i--){
                if(str1[i] != '/'){
                        str1[i] = 0;
                }
                else{
                        str1[i] = '\0';
                        break;
                }

        }
}


void open_directory(int file, struct dirent **namelist){
	if(wnd_now){
		if(namelist[file]->d_name[0] == '.'){
			minus_str(right_path);
		}
		else{
			strcat(right_path, "/");
			strcat(right_path, namelist[file]->d_name);
		}
		right_file_count = scandir(right_path, &namelist_right, NULL, alphasort);
		right_file = 1;
		start_row_right = 1;
	}
	else{
		if(namelist[file]->d_name[0] == '.'){
			minus_str(left_path);
		}
		else{
			strcat(left_path, "/");
			strcat(left_path, namelist[file]->d_name);
		}
		left_file_count = scandir(left_path, &namelist_left, NULL, alphasort);
		left_file = 1;
		start_row_left = 1;
	}
}


void display_table(WINDOW* win, struct dirent **namelist, int file_count, int file, bool wnd_sel, bool wnd, int start_row){
	
	int height = getmaxy(win) - 5;

  	werase(win);
  	box(win, 0, 0);

  	mvwprintw(win, 1, 1, "%s", "--Name--");
	for(int i = start_row; i < height + start_row && i < file_count; ++i){
		if(wnd_sel == wnd && i == file){
			wattron(win, A_REVERSE);
		}
		wattron(win, COLOR_PAIR(1));
		mvwprintw(win, i + 2 - start_row, 1, "%s", namelist[i]->d_name);
		wattroff(win, COLOR_PAIR(1));
		if(wnd_sel == wnd && i == file){
                        wattroff(win, A_REVERSE);
                }
		mvwprintw(win, getmaxy(win) - 2, 1, "Selected: %s", namelist[file]->d_name);
  		wrefresh(win);	
	}
		
}

