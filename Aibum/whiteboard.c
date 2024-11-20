#include "include/whiteboard.h"

int **joint_map(int **lcdbuf, int dh, int dw, int **init, int eh, int ew, int index, int indey)
{
    for (int i = 0; i < dh; i++)
    {
        for (int j = 0; j < dw; j++)
        {
            if (i >= indey && i < indey + eh && j >= index && j < index + ew)
            {
                lcdbuf[i][j] = init[i - indey][j - index];
            }
        }
    }
}

void main(int argc, char const *argv[])
{
    lcdbuf = load_bmp_as_argb("image/whiteboard.bmp");
    int **board = load_bmp_as_argb("image/whitecanvas.bmp");
    work_status = load_bmp_as_argb("image/select.bmp");
    drow_status = load_bmp_as_argb("image/drow.bmp");
    un_status_0 = load_bmp_as_argb("image/Un_0.bmp");
    un_status_1 = load_bmp_as_argb("image/Un_1.bmp");
    re_status_0 = load_bmp_as_argb("image/Re_0.bmp");
    re_status_1 = load_bmp_as_argb("image/Re_1.bmp");
    lcdbuf = joint_map(lcdbuf, 480, 800, board, 700, 430, 0, 50);
    
    show_mmap(lcdbuf);
    radius = 10;
    color_ = WHITE;
    save_count = 0;
    draw_pan_size = 5;
    BOARD_COLOR = WHITE; //画板颜色
    shape_status = 0; //0为画笔，1为矩形，3为三角形
    show_color_status(); //显示颜色
    show_status(un_status_0,0,50,48,48);//撤销
    show_status(re_status_0,0,100,48,48);//恢复
    show_pan_size(draw_pan_size);//画笔大小
    printf("whiteboard\n");
    show_borad_font("请选择画板颜色");
    select_board_color();//选择画板颜色
    creat_stack_list();//创建栈
    show_Undo(Undo->next->data);//显示当前画板颜色
    int a, b;
    while (1)
    {
        
        touch_wait(&a, &b);
        if(a < 700 && b > 50)
        {  
            show_drow();
            printf("111111111111");
        }
        else if(a > 755 && b < 50)
        {
            Undo = delete_list_stack(Undo);
            free(Undo);
            Redo = delete_list_stack(Redo);
            free(Redo);
            lcdbuf = delete_inmage_data(lcdbuf,480, 800);
            board = delete_inmage_data(board, 700, 430);
            work_status = delete_inmage_data(work_status, 48, 48);
            drow_status = delete_inmage_data(drow_status, 48, 48);
            un_status_0 = delete_inmage_data(un_status_0, 48, 48);
            un_status_1 = delete_inmage_data(un_status_1, 48, 48);
            re_status_0 = delete_inmage_data(re_status_0, 48, 48);
            re_status_1 = delete_inmage_data(re_status_1, 48, 48);
            break;
        }
        else
        {
            printf("xxxxxxxxxx");
            boardfun();

        }

    }
    return 0;
}

