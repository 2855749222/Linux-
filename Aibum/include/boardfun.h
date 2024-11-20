#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>
#include "whiteboard.h"
// #include "list.h"
int show_color_status();
int boardfun();
void out_picture(int **lcdbuf,int i);
void clear_board();
void select_board_color();
#endif