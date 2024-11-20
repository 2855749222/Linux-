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
    char buf[480 * 800 * 4] = {0};

    for (size_t i = 0; i < 480 * 800 * 4; i += 4)
    {
        buf[i + 3] = 0; // A
        buf[i + 2] = 0; // R
        buf[i + 1] = 0; // G
        buf[i] = 255;   // B
    }

    write(lcd_fd, buf, 800 * 480 * 4);

    close(lcd_fd);

    return 0;
}
