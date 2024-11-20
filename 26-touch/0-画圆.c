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

#define BLACK 0x00000000  // 黑色
#define RED 0x00ff0000    // 红色
#define GREEN 0x0000ff00  // 绿色
#define YELLOW 0x00ffff00 // 黄色

int main()
{

    int lcd_fd = open("/dev/fb0", O_RDWR);
    int(*lcd_mmap)[800] = (int(*)[800])mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);

    // for (size_t row = 0; row < 480; row++)
    // {
    //     for (size_t col = 0; col < 800; col++)
    //     {
    //         lcd_mmap[row][col] = RED;
    //     }
    // }

    // 画方块
    // for (size_t row = 0; row < 480; row++)
    // {
    //     for (size_t col = 0; col < 800; col++)
    //     {

    //         if (row > 100 && row < 200 && col > 100 && col < 300)
    //         {
    //             lcd_mmap[row][col] = RED;
    //         }
    //         else
    //         {
    //             lcd_mmap[row][col] = GREEN;
    //         }
    //     }
    // }

    int rx = 300, ry = 100, radius = 100;
    int w = 200, h = 100, x = 0, y = 0;
    while (1)
    {

        // for (size_t row = 0; row < 480; row++)
        // {
        //     // printf("%d  %lf\n", (row - 200) * (row - 200), pow((double)abs((row - 200)), 2));
        //     for (size_t col = 0; col < 800; col++)
        //     {
        //         // 圆心点是300 300
        //         // if ((row - 200) * (row - 200) + (col - 200) * (col - 200) <= 100 * 100)
        //         if (pow((double)abs((row - ry)), 2) + pow((double)abs((col - rx)), 2) <= pow((double)radius, 2))
        //         {
        //             lcd_mmap[row][col] = RED;
        //         }
        //         else
        //         {
        //             lcd_mmap[row][col] = GREEN;
        //         }
        //     }
        // }

        for (size_t row = 0; row < 480; row++)
        {
            for (size_t col = 0; col < 800; col++)
            {

                if (row > y && row < (h + y) && col > x && col < (w + x))
                {
                    lcd_mmap[row][col] = RED;
                }
                else
                {
                    lcd_mmap[row][col] = GREEN;
                }
            }
        }

        usleep(1000 * 16.7);

        // rx += 10;
        x += 10;
        x = x % 800;
    }

    // printf("%d %lf %d\n", 10 * 10, pow((double)10, 2), 100 == 100.0000);
    // printf("%lf\n", (double)10);

    munmap(lcd_mmap, 800 * 480 * 4);
    close(lcd_fd);

    return 0;
}
