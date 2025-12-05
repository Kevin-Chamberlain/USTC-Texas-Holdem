#ifndef MENU_H
#define MENU_H

void clear_screen();
void move_cursor(int row, int col);
void set_color(int color);
void reset_color();
void display_welcome(int cursor_row);
int do_welcome();
void display_work(int se_cursor_row);
int do_work();
#endif //MENU_H