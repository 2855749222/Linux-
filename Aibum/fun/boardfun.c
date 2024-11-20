#include "../include/boardfun.h"
int show_color_status()//显示当前颜色
{
    // if (lcdbuf == NULL)
    // {
    //     return -1;
    // }
    // 1. 打开液晶屏文件

    int lcdFd = open("/dev/fb0", O_RDWR);
    if (lcdFd == -1)
    {
        perror("open lcd error");

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
            if (i >= 405 && i < 450 && j >= 728 && j < 774)
            {
                lcd_p[i * 800 + j] = color_;
            }
        }
    }

    munmap(lcd_p, 800 * 480 * 4);

    close(lcdFd);
    return 1;
}
void out_picture(int **lcdbuf, int i)//将画图数据输出到lcd
{
    printf("out_picture\n");
    char buf[430 * 700 * 4] = {0};  // 存储画图中的数据
    char buf1[430 * 700 * 3] = {0}; // 存储生成bmp图片的数据
    int src_index = 0;

    // 将图片数据存储到buf中
    for (int i = 0; i < 430; i++)
    {
        for (int j = 0; j < 700; j++)
        {
            // 假设 lcdbuf[i][j] 是一个整数，包含了 RGBA 颜色值
            // 这里简单地将每个颜色分量存储在 buf 中
            // 注意：这里假设 lcdbuf 中的值是正确的，并且按照 RGBA 顺序排列
            buf[src_index++] = (lcdbuf[i][j] >> 16) & 0xFF; // R
            buf[src_index++] = (lcdbuf[i][j] >> 8) & 0xFF;  // G
            buf[src_index++] = lcdbuf[i][j] & 0xFF;         // B
            buf[src_index++] = (lcdbuf[i][j] >> 24) & 0xFF; // A（这里不使用，但保持一致性）
        }
    }
    int j = 0;
    // 将buf中的数据存储到buf1中,并且将rgb格式转换为bgr格式,四个字节转换为三个字节一个像素
    for (int i = 0; i < 430 * 700; i++)
    {
        int index = i * 4;
        buf1[j++] = buf[index + 2]; // B
        buf1[j++] = buf[index + 1]; // G
        buf1[j++] = buf[index];     // R
    }

    char temp[700 * 3] = {0};
    printf("out_picture \n");
    // 上下反转
    for (int i = 0; i < 215; i++)
    {
        // 拷贝一行
        for (int j = 0; j < 700 * 3; j++)
        {
            temp[j] = buf1[i * 700 * 3 + j];
        }
        // 交换行
        for (int j = 0; j < 700 * 3; j++)
        {
            buf1[i * 700 * 3 + j] = buf1[(430 - i - 1) * 700 * 3 + j];
            buf1[(430 - i - 1) * 700 * 3 + j] = temp[j];
        }
    }
    char path[256];
    i %= 10;
    snprintf(path, sizeof(path), "/mnt/share/aibum/draw_save/%d.bmp", i);
    // 将像素转换为图片
    int fd1 = open(path, O_WRONLY | O_CREAT, 0666); // 打开图片进行写入，如果文件不存在则创建
    if (fd1 < 0)
    {
        perror("open");
        return;
    }

    lseek(fd1, 54, SEEK_SET); // 定位到图片数据位置
    if (write(fd1, buf1, 430 * 700 * 3) != 430 * 700 * 3)
    {
        perror("write");
        close(fd1);
        return;
    }
    if (close(fd1) < 0)
    {
        perror("close");
    }
    printf("out_picture success\n");
}
void clear_board()//清空画板
{
    stack *newNode = malloc(sizeof(stack));
    newNode->data = initdata();
    for (int i = 0; i < 430; i++)
    {
        for (int j = 0; j < 700; j++)
        {
            newNode->data[i][j] = BOARD_COLOR;
        }
    }
    newNode->next =  Undo->next;
    Undo->next = newNode;
    show_Undo(Undo->next->data);
}
int boardfun()//画板功能区
{
    int y, x;
    while (1)
    {

       
        touch_wait(&x, &y);//获取坐标
        if (x < 700 && y > 60)
        {
            show_status(drow_status, 0, 170, 48, 48);//切换工作区状态
            show_drow();//进入画板工作区
        }
        else if (y < 90 && y > 54 && x > 707 && x < 746)
        {
            color_ = RED;
            show_color_status();//切换颜色状态
        }
        else if (y < 90 && y > 54 && x > 757 && x < 800)
        {
            color_ = ORANGE;
            show_color_status();
        }
        else if (y < 140 && y > 100 && x > 707 && x < 746)
        {
            color_ = YELLOW;
            show_color_status();
        }
        else if (y < 140 && y > 100 && x > 757 && x < 800)
        {
            color_ = GREEN;
            show_color_status();
        }
        else if (y < 190 && y > 150 && x > 707 && x < 746)
        {
            color_ = SKY_BLUE;
            show_color_status();
        }
        else if (y < 190 && y > 150 && x > 757 && x < 800)
        {
            color_ = BLUE;
            show_color_status();
        }
        else if (y < 240 && y > 200 && x > 707 && x < 746)
        {
            color_ = BROWN;
            show_color_status();
        }
        else if (y < 240 && y > 200 && x > 757 && x < 800)
        {
            color_ = PINK;
            show_color_status();
        }
        else if (y < 290 && y > 250 && x > 707 && x < 746)
        {
            color_ = PURPLE;
            show_color_status();
        }
        else if (y < 290 && y > 250 && x > 757 && x < 800)
        {
            color_ = BLACK;
            show_color_status();
        }
        else if (y < 363 && y > 323 && x > 727 && x < 777)//橡皮擦
        {
            color_ = BOARD_COLOR;//获取白板背景颜色
            show_color_status();
        }
        else if (y <= 50 && y > 0 && x > 450 && x < 500) // clear board
        {
            clear_board();//清空画板
        }
        else if (y <= 50 && y > 0 && x > 550 && x < 600) //+
        {
            if (draw_pan_size < 100)
                draw_pan_size += 5;
            show_pan_size(draw_pan_size);
        }
        else if (y <= 50 && y > 0 && x > 650 && x < 700) //-
        {
            if (draw_pan_size > 5)
                draw_pan_size -= 5;
            show_pan_size(draw_pan_size);
        }
        else if (y <= 50 && y >= 0 && x >= 50 && x <= 100) // 撤销
        {
            if (Undo->next->next == NULL)//如果撤销列表为空
            {
                continue;
            }

            if (Undo->next->next->next == NULL) // 如果撤销列表为空
            {
                show_status(un_status_0, 0, 50, 48, 48);//更改撤销图标
            }
            Redo = insert__Redo_tlist(Redo); // 插入到Redo栈中
            show_status(re_status_1, 0, 100, 48, 48);

            Undo = poplist(Undo); 
        }
        else if (y <= 50 && y >= 0 && x >= 100 && x <= 150) // 重做
        {
            if (Redo->next == NULL)
            {
                continue;
            }
            if (Redo->next->next == NULL) // 如果Redo列表为空
            {
                show_status(re_status_0, 0, 100, 48, 48);
            }
            Redo = pop_Redo_list(Redo); // 弹出Redo

            show_status(un_status_1, 0, 50, 48, 48);
        }
        else if (y <= 50 && y >= 0 && x >= 250 && x <= 300) //圆形
        {
            printf("shape_status = 0");
            shape_status = 0;
        }
        else if (y <= 50 && y >= 0 && x >= 300 && x <= 350) //矩形
        {
            printf("shape_status = 1");
            shape_status = 1;
        }
        else if (y <= 50 && y >= 0 && x >= 350 && x <= 400) //三角型
        {
             printf("shape_status = 2");
            shape_status = 2;
        }
        else if (x > 755 && y < 50) //退出
        {
            return 0;
        }
        else if (y < 50 && x < 50) // 保存
        {
            printf("save\n");
            show_borad_font("保存成功");

            out_picture(Undo->next->data, save_count);
            save_count++;
        }
    }
}
void select_board_color()
{
    int y, x;
    while (1)
    {

        // x y 互换
        touch_wait(&x, &y);
        if (x < 700 && y > 50)
        {
           break;
        }
        else if (y < 90 && y > 54 && x > 707 && x < 746)
        {
            BOARD_COLOR = RED;
            color_ = RED;
            show_color_status();
        }
        else if (y < 90 && y > 54 && x > 757 && x < 800)
        {
            BOARD_COLOR = ORANGE;
            color_ = ORANGE;
            show_color_status();
        }
        else if (y < 140 && y > 100 && x > 707 && x < 746)
        {
            BOARD_COLOR = YELLOW;
            color_ = YELLOW;
            show_color_status();
        }
        else if (y < 140 && y > 100 && x > 757 && x < 800)
        {
            BOARD_COLOR = GREEN;
            color_ = GREEN;
            show_color_status();
        }
        else if (y < 190 && y > 150 && x > 707 && x < 746)
        {
            BOARD_COLOR = SKY_BLUE;
            color_ = SKY_BLUE;
            show_color_status();
        }
        else if (y < 190 && y > 150 && x > 757 && x < 800)
        {
            BOARD_COLOR = BLUE;
            color_ = BLUE;
            show_color_status();
        }
        else if (y < 240 && y > 200 && x > 707 && x < 746)
        {
            BOARD_COLOR = BROWN;
            color_ = BROWN;
            show_color_status();
        }
        else if (y < 240 && y > 200 && x > 757 && x < 800)
        {
            BOARD_COLOR = PINK;
            color_ = PINK;
            show_color_status();
        }
        else if (y < 290 && y > 250 && x > 707 && x < 746)
        {
            BOARD_COLOR = PURPLE;
            color_ = PURPLE;
            show_color_status();
        }
        else if (y < 290 && y > 250 && x > 757 && x < 800)
        {
            BOARD_COLOR = BLACK;
            color_ = BLACK;
            show_color_status();
        }
    }
}