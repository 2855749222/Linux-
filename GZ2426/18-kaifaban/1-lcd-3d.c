#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
int main()
{
    int lcd_fd = open("/dev/fb0", O_RDWR);

    if (lcd_fd == -1)
    {
        perror("open errar");
        return -1;
    }
    int(* lcd_p)[800] = (int(*)[800])mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    int arr[480][800] = {0};
    if( lcd_p == MAP_FAILED)
    {
        printf("error\n");
        return -1;
    }
    int black = 0x00000000;
    int white = 0x00ffffff;
    int gree = 0x0000ff00;
    int red = 0x00ff0000;
    for (int i = 0; i < 160; i++)
    {

        for (int j = 0; j < 800; j++)
        {
            arr[i][j] = black;
            arr[160 + i][j] = white;
            arr[320 + i][j] = gree;
        }
    }
    for (int i = 0; i <= 240; i++)
    {
        for (int j = 0; j <= (i + i / 4); j++)
        {
            arr[i][j] = red;
            arr[480 - i][j] = red;
        }
    }
     for (int i = 0; i <= 480; i++)
    {
        for (int j = 0; j <= 800; j++)
        {
            lcd_p[i][j] = arr[i][j];

        }
    }
    
    munmap(lcd_p, 480 * 800 * 4);
    close(lcd_fd);
    return 0;
}