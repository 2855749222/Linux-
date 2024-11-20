#ifndef LIST_H
#define LIST_H

#include "head.h"
#include "main.h"

typedef struct SnakeNode
{
    int x;
    int y;
    int dir;
    struct SnakeNode *next;
} Snake;

typedef struct Food
{
    int x;
    int y;
} Food;
enum DIR
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
Snake *head, *newNode, *tail, *temp;
int Nodenumb;
int speed;
int Snaketail_x;
int Snaketail_y;
int SnakeNode_size;
int Snaketail_dir;
int Food_x;
int Food_y;
int Newdir;
int tailx;
int taily;
int score;
int **lcdbuf;
int **Snake_body;
int **Foot_dr;
int **Snake_head;
int **Snake_tail;
#define WHITE 0x00ffffff
#define RED 0x00ff0000
#define YELLOW 0x00fff200 // 黄色

void initSnake(int speed);
void *gameplay(void *arg);
void drowSnake();
void addSnakeNode();
void drowfood(int color);
void moveSnake(Snake *Node, int dir);
void clearbrg(int x, int y, int heigth, int width);
void *create_foot(void *arg);
void generateFoodPosition();
void game_over();

int nn;
#endif