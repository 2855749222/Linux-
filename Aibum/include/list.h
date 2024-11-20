#ifndef LIST_H
#define LIST_H

#include "whiteboard.h"
typedef struct liststack
{
    int **data;
    struct liststack * next;
}stack;
stack * Undo,* Redo;
void creat_stack_list();//创建栈
int show_Undo(int **  lcdbuf);//显示撤销
stack * insertlist(stack * head);//插入栈
stack * poplist(stack * head);//弹出栈
int ** get_status(int **board_status, int **new_status);//获取状态
int **initdata();//初始化数据
stack * insert__Redo_tlist(stack *head);//插入Redo
stack *pop_Redo_list(stack *head); //弹出Redo
stack *delete_list_stack(stack *head);//删除栈
int ** delete_inmage_data(int**array ,int row,int col);// 删除图片数据
#endif