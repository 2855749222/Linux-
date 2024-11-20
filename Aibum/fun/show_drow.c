#include "../include/show_drow.h"
int show_status(int **lcdbuf, int poy, int pox, int height, int width)
{
    if (lcdbuf == NULL)
    {
        return -1;
    }
    // 1. 打开液晶屏文件

    int lcdFd = open("/dev/fb0", O_RDWR);
    if (lcdFd == -1)
    {
        perror("open lcd error");
        free(lcdbuf);
        return -1;
    }
    // 7. 映射液晶屏的内存
    int *lcd_p = (int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcdFd, 0);
    if (lcd_p == MAP_FAILED)
    {
        perror("mmap error");
        close(lcdFd);
        return -1;
    }
    // 8. 显示图片s
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if (i >= poy && i < poy + height - 3 && j >= pox && j < pox + width)
            {
                lcd_p[i * 800 + j] = lcdbuf[i - poy][j - pox];
            }
        }
    }
    munmap(lcd_p, 800 * 480 * 4);
    close(lcdFd);
    return 1;
}
void triangle(int (*lcd_mmap)[800], int x1, int y1, int x2, int y2, int x3, int y3)
{
    // flag:代表本三角形在本直线的左边（0）还是右边（1）（左边右边是抽象概念）
    int i, j, flag1 = 0, flag2 = 0, flag3 = 0;
    float A1, B1, C1, A2, B2, C2, A3, B3, C3;
    // 1号点与2号点的直线方程的A，B，C
    A1 = y2 - y1;
    B1 = x1 - x2;
    C1 = x2 * y1 - x1 * y2;
    // 2号点与3号点的直线方程的A，B，C
    A2 = y2 - y3;
    B2 = x3 - x2;
    C2 = x2 * y3 - x3 * y2;
    // 1号点与3号点的直线方程的A，B，C
    A3 = y3 - y1;
    B3 = x1 - x3;
    C3 = x3 * y1 - x1 * y3;

    // 判断第三个点与直线的相对位置
    if (x3 * A1 + y3 * B1 + C1 > 0)
        flag1 = 1;
    if (x1 * A2 + y1 * B2 + C2 > 0)
        flag2 = 1;
    if (x2 * A3 + y2 * B3 + C3 > 0)
        flag3 = 1;

    for (i = 0; i < 480; i++)
    {
        for (j = 0; j < 800; j++)
        {
            if (flag1 == 1)
            {
                if (flag2 == 1)
                {
                    if (j * A1 + i * B1 + C1 > 0 && j * A2 + i * B2 + C2 > 0 && j * A3 + i * B3 + C3 < 0)
                    {
                        lcd_mmap[i][j] = color_;
                        Undo->next->data[i - 50][j] = color_;
                    }
                }
                else
                {
                    if (flag3 == 1)
                    {
                        if (j * A1 + i * B1 + C1 > 0 && j * A2 + i * B2 + C2 < 0 && j * A3 + i * B3 + C3 > 0)
                        {
                            lcd_mmap[i][j] = color_;
                            Undo->next->data[i - 50][j] = color_;
                        }
                    }
                    else
                    {
                        if (j * A1 + i * B1 + C1 > 0 && j * A2 + i * B2 + C2 < 0 && j * A3 + i * B3 + C3 < 0)
                        {
                            lcd_mmap[i][j] = color_;
                            Undo->next->data[i - 50][j] = color_;
                        }
                    }
                }
            }
            else
            {
                if (flag2 == 0)
                {
                    if (j * A1 + i * B1 + C1 < 0 && j * A2 + i * B2 + C2 < 0 && j * A3 + i * B3 + C3 > 0)
                    {
                        lcd_mmap[i][j] = color_;
                        Undo->next->data[i - 50][j] = color_;
                    }
                }
                else
                {
                    if (flag3 == 1)
                    {
                        if (j * A1 + i * B1 + C1 < 0 && j * A2 + i * B2 + C2 > 0 && j * A3 + i * B3 + C3 > 0)
                        {
                            lcd_mmap[i][j] = color_;
                            Undo->next->data[i - 50][j] = color_;
                        }
                    }
                    else
                    {
                        if (j * A1 + i * B1 + C1 < 0 && j * A2 + i * B2 + C2 > 0 && j * A3 + i * B3 + C3 < 0)
                        {
                            lcd_mmap[i][j] = color_;
                            Undo->next->data[i - 50][j] = color_;
                        }
                    }
                }
            }
        }
    }
}
// int show_drow()
// {
//     show_status(drow_status, 0, 170, 48, 48); // 显示画笔
//     delete_list_stack(Redo);                  // 清空恢复栈
//     show_status(re_status_0, 0, 100, 48, 48); // 显示恢复
//     Undo = insertlist(Undo);                  // 插入预存节点
//     int drow_count = 0;
//     int lcd_fd = open("/dev/fb0", O_RDWR);
//     int(*lcd_mmap)[800] = (int(*)[800])mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
//     int x = -1, y = -1; // 初始值是-1
//     int touch_fd = open("/dev/input/event0", O_RDWR);
//     if (touch_fd < 0)
//     {
//         printf("open touch failed\n");
//         return -1;
//     }
//     while (1)
//     {

//         if (drow_count == 1)
//         {
//             Undo = insertlist(Undo);
//             drow_count = 0;
//         }

//         show_status(drow_status, 0, 170, 48, 48);
//         while (1)
//         {

//             struct input_event touch_event;
//             int read_ret = read(touch_fd, &touch_event, sizeof(struct input_event));

//             if (read_ret < 0)
//             {
//                 perror("read touch failed\n");
//                 return -1;
//             }
//             if (touch_event.type == EV_ABS)
//             {
//                 if (touch_event.code == ABS_X)
//                 {
//                     // x = touch_event.value; // 蓝色板子
//                     x = touch_event.value * 800 / 1024; // 黑色板子
//                 }
//                 else if (touch_event.code == ABS_Y)
//                 {
//                     // y = touch_event.value;
//                     y = touch_event.value * 480 / 600;
//                 }
//             }

//             if (touch_event.type == EV_SYN)
//             {
//                 printf("x=%d,y=%d\n", x, y);

//                 // 画出小球
//                 for (size_t row = 0; row < 480; row++)
//                 {
//                     // printf("%d  %lf\n", (row - 200) * (row - 200), pow((double)abs((row - 200)), 2));
//                     for (size_t col = 0; col < 800; col++)
//                     {
//                         // 圆心点是300 300
//                         if ((row - y) * (row - y) + (col - x) * (col - x) <= radius * radius && x <= 700 && y >= 50 && row > 50 && col < 700)
//                         {
//                             lcd_mmap[row][col] = color_;
//                             // Undo Stack[row][col] = color_;

//                             Undo->next->data[row - 50][col] = color_; // 保存到undo栈
//                         }

//                         else if ((col > 700 && (col <= 728 || col > 774 || row < 405 || row >= 450)) && (row > 45))
//                         {
//                             lcd_mmap[row][col] = lcdbuf[row][col];
//                         }
//                     }
//                 }
//             }

//             if (touch_event.type == EV_KEY && touch_event.code == BTN_TOUCH && touch_event.value == 0)
//             {
//                 drow_count = 1;
//                 if (Undo->next->next != NULL) // 如果撤销列表为空
//                 {
//                     show_status(un_status_1, 0, 50, 48, 48);
//                 }

//                 break;
//             }
//         }
//         if (x > 700 || y < 50)
//         {
//              Undo = poplist(Undo);
//             if(Undo->next->next == NULL)
//             {
//                 show_status(un_status_0, 0, 50, 48, 48);
//             }
//             printf("1return");
//             close(touch_fd);
//             show_status(work_status, 0, 170, 48, 48); // 显示工作区状态
//                              // 弹出预存节点
//             break;
//         }
//     }
//     close(touch_fd);
//     return 0;
// }

void draw_line(int (*lcd_mmap)[800], int x1, int y1, int x2, int y2, int R)
{

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy; // 初始化误差项
    while (1)
    {
        if (shape_status == 0)
        {
            for (int i = -R; i <= R; i++)
            {
                for (int j = -R; j <= R; j++)
                {
                    if (i * i + j * j <= (R * R))
                    {
                        int screenX = x1 + j;
                        int screenY = y1 - i; // 翻转Y轴，因为屏幕坐标系与数学坐标系不同
                        if (screenX >= 0 && screenX < 700 && screenY >= 50 && screenY < 480)
                        {
                            lcd_mmap[screenY][screenX] = color_;
                            // printf("x1:%d,y1:%d,x2:%d,y2:%d\n", x1, y1, x2, y2);
                            Undo->next->data[screenY - 50][screenX] = color_;
                        }
                    }
                }
            }
        }
        else if (shape_status == 1)
        {
            for (int i = -R / 2; i <= R / 2; i++)
            {
                for (int j = -R / 2; j <= R / 2; j++)
                {
                    int nx = x1 + j;
                    int ny = y1 + i;
                    if (nx >= 0 && nx < 700 && ny >= 50 && ny < 480)
                    {
                        lcd_mmap[ny][nx] = color_;
                        Undo->next->data[ny - 50][nx] = color_;
                    }
                }
            }
        }
        else if (shape_status == 2)
        {
            for (int i = -R; i <= R; i++)
            {
                for (int j = -R; j <= R; j++)
                {
                    if (i * i + j * j <= (R * R))
                    {
                        int screenX = x1 + j;
                        int screenY = y1 - i; // 翻转Y轴，因为屏幕坐标系与数学坐标系不同
                        if (screenX >= 0 && screenX < 700 && screenY >= 50 && screenY < 480)
                        {
                            lcd_mmap[screenY][screenX] = color_;
                            // printf("x1:%d,y1:%d,x2:%d,y2:%d\n", x1, y1, x2, y2);
                            Undo->next->data[screenY - 50][screenX] = color_;
                        }
                    }
                }
            }
            //  if (x1 >= 0 && x1 < 700 && y1 >= 0 && y1 < 430) 
            //  {  
            //     lcd_mmap[y1 + 50][x1] = color_; // 假设屏幕原点在(0,50)  
            //     Undo->next->data[y1][x1] = color_;;
            //  }  
        }
        if (x1 == x2 && y1 == y2)
            break;

        // 计算新的误差项的两倍
        int e2 = 2 * err;

        // 如果e2大于-dy，则向x方向移动
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        // 如果e2小于dx，则向y方向移动
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}
void draw_triangle(int (*lcd_mmap)[800], int x1, int y1, int x2, int y2, int x3, int y3, int color1) {  
    draw_line(lcd_mmap, x1, y1, x2, y2, color1);  
    draw_line(lcd_mmap, x2, y2, x3, y3, color1);  
    draw_line(lcd_mmap, x3, y3, x1, y1, color1);  
}
int show_drow()
{
    // 初始化绘制状态图标
    show_status(drow_status, 0, 170, 48, 48);

    // 清空恢复栈
    delete_list_stack(Redo);

    // 初始化恢复状态图标
    show_status(re_status_0, 0, 100, 48, 48);

    // 插入新的预存节点到撤销栈
    Undo = insertlist(Undo);

    // 打开帧缓冲设备文件，并将其映射到内存
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd < 0)
    {
        perror("open lcd_fd failed");
        return -1;
    }
    int(*lcd_mmap)[800] = (int(*)[800])mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (lcd_mmap == MAP_FAILED)
    {
        perror("mmap failed");
        close(lcd_fd);
        return -1;
    }

    // 打开触摸事件设备文件
    int touch_fd = open("/dev/input/event0", O_RDWR);
    if (touch_fd < 0)
    {
        perror("open touch_fd failed");
        munmap(lcd_mmap, 800 * 480 * 4);
        close(lcd_fd);
        return -1;
    }

    int x_start = -1, y_start = -1; // 起始点坐标，初始值设为-1表示未设置
    int x_end = -1, y_end = -1;     // 终点坐标，初始值设为-1表示未设置
    int x_sn = -1,y_sn = -1;
    int sn_status = 1; // 标记是否需要绘制
    int drawing = 0;                // 标记是否正在绘制
    int drow_count = 0;
    // 主循环
    while (1)
    {
        // 绘制状态更新
        show_status(drow_status, 0, 170, 48, 48);
        if (drow_count == 1)
        {
            Undo = insertlist(Undo);
            drow_count = 0;
        }

        // 等待触摸事件
        while (1)
        {
            struct input_event touch_event;
            int read_ret = read(touch_fd, &touch_event, sizeof(struct input_event));

            if (read_ret < 0)
            {
                perror("read touch failed");
                close(touch_fd);
                munmap(lcd_mmap, 800 * 480 * 4);
                close(lcd_fd);
                return -1;
            }

            // 处理触摸事件
            if (touch_event.type == EV_ABS)
            {
                if (touch_event.code == ABS_X)
                {
                    x_end = touch_event.value * 800 / 1024; // 计算触摸点的 x 坐标
                }
                else if (touch_event.code == ABS_Y)
                {
                    y_end = touch_event.value * 480 / 600; // 计算触摸点的 y 坐标
                }
            }

            // 触摸事件同步，绘制线段
            if (touch_event.type == EV_SYN)
            {
                if (drawing)
                {
                    if (x_start != -1 && y_start != -1 && x_end != -1 && y_end != -1)
                    {
                        // 如果起始点已设置，绘制从 (x_start, y_start) 到 (x_end, y_end) 的直线
                        if(shape_status != 2)
                        {
                            draw_line(lcd_mmap, x_start, y_start, x_end, y_end, draw_pan_size);
                           
                        }
                       
                        // 保存绘制内容到撤销栈
                    }
                    if(shape_status == 2 && sn_status)
                    {
                        x_sn = x_end;
                        y_sn = y_end;
                        sn_status = 0;
                    }
                }
                // 更新起始点为当前触摸点
                
                x_start = x_end;
                y_start = y_end;
            }

            // 触摸释放事件
            if (touch_event.type == EV_KEY && touch_event.code == BTN_TOUCH)
            {
                printf("x_end = %d, y_end = %d\n", x_end, y_end);
                if (touch_event.value == 1) // 触摸按下
                {
                    drawing = 1;
                    x_start = x_end;
                    y_start = y_end;
                }
                else if (touch_event.value == 0) // 触摸释放
                {
                    drawing = 0;
                    x_start = -1; // 如果不需要立即开始新绘制，可以重置
                    y_start = -1;
                    if (shape_status == 2)
                    {
                         draw_triangle(lcd_mmap, x_sn, y_sn, x_end, y_end,x_end - draw_pan_size ,y_sn - draw_pan_size, draw_pan_size);
                    }
                    y_sn = -1;
                    x_sn = -1;
                    sn_status = 1;
                    drow_count = 1;
                    if (Undo->next->next != NULL) // 如果撤销列表为空
                    {
                        show_status(un_status_1, 0, 50, 48, 48);
                    }
                    break;
                }
            }
        }

        // 处理触摸超出边界的情况
        if (y_end < 50 || x_end > 700)
        {
            printf("x_end");
            Undo = poplist(Undo); // 从撤销栈中弹出一个节点
            if (Undo->next->next == NULL)
            {
                show_status(un_status_0, 0, 50, 48, 48); // 显示恢复状态图标
            }
            printf("1return");
            show_status(work_status, 0, 170, 48, 48); // 显示工作区状态图标
            break;                                    // 跳出外层循环，结束函数
        }
    }

    // 关闭触摸设备文件
    close(touch_fd);
    munmap(lcd_mmap, 800 * 480 * 4); // 解除映射
    return 0;                        // 函数成功执行完毕
}
