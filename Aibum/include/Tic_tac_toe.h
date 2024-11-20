#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "head.h"
#include "get_touch_index.h"
#include "load_bmp_as_argb.h"
#include "show_mmap.h"
#include "font.h"

void cleararray(char **Chessboard);
int insert(char **Chessboard, int num, char ch);
void palygame(char **Chessboard,int **lcdbuf);
int same(char **Chessboard);
void insertpiece(int index, int indey, int **piece, int **lcdbuf);
int insertmap(int **lcdbuf, int **piece,char **Chessboard,char C);
void showfont(char *buf);
void Gameover(char *buf);
int playone;
int playtwe;
#endif