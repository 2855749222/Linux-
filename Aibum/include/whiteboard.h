#ifndef BOARD.H
#define BOARD.H
#include "head.h"
#include "get_touch_index.h"
#include "load_bmp_as_argb.h"
#include "show_mmap.h"
#include "font.h"
#include "show_drow.h"
#include "boardfun.h"
#include "list.h"

int radius;
#define BLACK 0x00000000  // 黑色
#define RED 0x00ff0000    // 红色
#define GREEN 0x0022b14c  // 绿色
#define YELLOW 0x00fff200 // 黄色
#define ORANGE 0x00ff7f27 // 
#define SKY_BLUE 0x0000a2e8 
#define BLUE 0x003f48cc
#define BROWN 0x00880015
#define PINK 0x00ffaec9
#define PURPLE 0x00a349a4// 
#define WHITE 0x00ffffff
int color_;
int **work_status;
int **drow_status;
int **lcdbuf;
int **un_status_1;
int **un_status_0;
int **re_status_1;
int **re_status_0;
int save_count;
int draw_pan_size;
int BOARD_COLOR;
int shape_status;
#endif

