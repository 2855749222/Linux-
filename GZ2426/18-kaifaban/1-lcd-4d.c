#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <math.h>
#define WIDTH 800
#define HEIGHT 480
#define PITCH (WIDTH * 4) // 假设每个像素4个字节（32位色）
typedef struct list
{
    int midlex;
    int midley;
    int R;
    int vx;
    int vy;
    struct list *next;
} list;
int count = 0;
// 函数声明
void clear_screen(int *fbp, int width, int height);
void draw_circle(int *fbp, list *head, int color);
void update_position(list **head, int width, int height);
void all_ball(list *head, int *mem_p);
list *add_ball(list *head, int curx, int cury);
int main()
{
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1)
    {
        perror("Error opening framebuffer device");
        return EXIT_FAILURE;
    }

    // 获取屏幕信息（这里省略，因为示例中未使用）

    // 映射帧缓冲区到内存
    int *mem_p = (int *)mmap(NULL, WIDTH * HEIGHT * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (mem_p == MAP_FAILED)
    {
        close(lcd_fd);
        perror("Error mapping framebuffer device to memory");
        return EXIT_FAILURE;
    }

    // 初始化球的位置和速度
    list *head = malloc(sizeof(list));
    head->midlex = WIDTH / 2;
    head->midley = HEIGHT / 2;
    head->R = 150;
    head->vx = 4;
    head->vy = 4;
    head->next = NULL;
    int iterations = 10000; // 总迭代次数

    // 动画循环
    for (int count = 0; count < iterations; count++)
    {
        // clear_screen(mem_p, WIDTH, HEIGHT);

        // draw_circle(mem_p,head2, 0xFFFF00);
        draw_circle(mem_p, head, 0xF00000); // 绘制红色圆形
        update_position(&head, WIDTH, HEIGHT);
        // all_ball(head, mem_p);
        // update_position(&head2, WIDTH, HEIGHT);
        // sleep(1);
        // 可以在这里添加延时以减慢动画速度
        // usleep(10000); // 10毫秒
    }

    // 清理资源
    munmap(mem_p, WIDTH * HEIGHT * 4);

    close(lcd_fd);

    return 0;
}
// 遍历所有球
// void all_ball(list *head, int *mem_p)
// {
//     list *temp = head;
//     int i = 1;
//     while (temp != NULL)
//     {
//         printf("%d ", i);
//         i++;
//         draw_circle(mem_p, temp, 0xFF0000);
//         temp = temp->next;
//     }
// }
// 添加球
list *add_ball(list *head, int curx, int cury)
{

    list *newnode = malloc(sizeof(list));
    newnode->midlex = curx;
    newnode->midley = cury;
    newnode->R = (head)->R / 2;
    ((head)->vx) = ((head)->vx) * 2;
    ((head)->vy) = ((head)->vy) * 2;
    newnode->vx = -((head)->vx);
    newnode->vy = -((head)->vy);
    newnode->next = NULL;
    (head)->R = (head)->R / 2;
    (head)->next = newnode;

    return head;
}
// 清除屏幕的函数
// void clear_screen(int *fbp, int width, int height)
// {
//     memset(fbp, 0x00, width * height * 4); // 设置为黑色
// }

// 绘制圆形的函数
void draw_circle(int *fbp, list *head, int color)
{

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int inside_circle = 0;
            for (list *temp = head; temp != NULL; temp = temp->next)
            {
                int dx = x - temp->midlex;
                int dy = y - temp->midley;
                if (dx * dx + dy * dy <= temp->R * temp->R)
                {
                    inside_circle = 1;
                    break;
                }
            }
            if (inside_circle)
                fbp[(y * WIDTH) + x] = color;
            else
                fbp[(y * WIDTH) + x] = 0x00000000; // 黑色背景
        }
    }
}

// 更新球的位置和速度的函数
void update_position(list **node, int width, int height)
{
    list **head = node;
    list **temp = head;
    while ((*head != NULL))
    {
        (*head)->midlex += (*head)->vx;
        (*head)->midley += (*head)->vy;

        // 碰撞检测
        if ((*head)->midlex - (*head)->R <= 0 || (*head)->midlex + (*head)->R >= width)
        {
            (*head)->vx = -(*head)->vx;
            if (count < 8 && (*head)->R > 40)
            {
                list *temp = (*head)->next;
                (*head) = add_ball(*head, (*head)->midlex, (*head)->midley);
                (*head)->next->next = temp;
                count++;
            }
        }
        if ((*head)->midley - (*head)->R <= 0 || (*head)->midley + (*head)->R >= height)
        {
            (*head)->vy = -(*head)->vy;
            if (count < 8 && (*head)->R > 40)
            {
                list *temp = (*head)->next;
                (*head) = add_ball(*head, (*head)->midlex, (*head)->midley);
                (*head)->next->next = temp;
                count++;
            }
        }

        // 小球之间的碰撞检测
        // 碰撞检测与其他小球
        if ((*head)->R < 40)
        {
            list **temp1 = head;
            while (*temp1 != NULL)
            {
                if ((*temp1) != (*head))
                {
                    int dx = (*head)->midlex - (*temp1)->midlex;
                    int dy = (*head)->midley - (*temp1)->midley;
                    int distance_squared = dx * dx + dy * dy;
                    int min_distance_squared = ((*head)->R + (*temp1)->R) * ((*head)->R + (*temp1)->R);

                    if (distance_squared <= min_distance_squared)
                    {
                        // 碰撞反弹
                        (*head)->vx = -(*head)->vx;
                        // (*head)->vy = -(*head)->vy;
                        // (*temp1)->vx = -(*temp1)->vx;
                        (*temp1)->vy = -(*temp1)->vy;
                    }
                }
                temp1 = &(*temp1)->next;
            }
        }
        head = &(*head)->next;
    }
}