#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <math.h>
#include <linux/input.h>

#define BLACK 0x00000000  // 黑色
#define RED 0x00ff0000    // 红色
#define GREEN 0x0000ff00  // 绿色
#define YELLOW 0x00ffff00 // 黄色

int main()
{

    int lcd_fd = open("/dev/fb0", O_RDWR);
    int(*lcd_mmap)[800] = (int(*)[800])mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    int radius = 50;

    int x = -1, y = -1; // 初始值是-1

    int touch_fd = open("/dev/input/event0", O_RDWR);
    if (touch_fd < 0)
    {
        printf("open touch failed\n");
        return -1;
    }
    // printf("open touch success\n");

    struct input_event touch_event;
    while (1)
    {
        int read_ret = read(touch_fd, &touch_event, sizeof(struct input_event));
        // printf("%d %d %d\n", touch_event.type, touch_event.code, touch_event.value);
        if (read_ret < 0)
        {
            perror("read touch failed\n");
            return -1;
        }

        if (touch_event.type == EV_ABS)
        {
            if (touch_event.code == ABS_X)
            {
                // x = touch_event.value; // 蓝色板子
                x = touch_event.value * 800 / 1024; // 黑色板子
            }
            else if (touch_event.code == ABS_Y)
            {
                // y = touch_event.value;
                y = touch_event.value * 480 / 600;
            }
        }

        if (touch_event.type == EV_SYN)
        {
            printf("x=%d,y=%d\n", x, y);

            // 画出小球
            for (size_t row = 0; row < 480; row++)
            {
                // printf("%d  %lf\n", (row - 200) * (row - 200), pow((double)abs((row - 200)), 2));
                for (size_t col = 0; col < 800; col++)
                {
                    // 圆心点是300 300
                    if ((row - y) * (row - y) + (col - x) * (col - x) <= 10 * 10)
                    {
                        lcd_mmap[row][col] = YELLOW;
                    }
            
                }
            }

           
        }
         if(touch_event.type == EV_KEY && touch_event.code == BTN_TOUCH && touch_event.value == 0)
        {
            break;
        }
    }

    close(touch_fd);
    return 0;
}
