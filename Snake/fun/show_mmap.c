#include "../include/show_mmap.h"

/// @brief 
/// @param lcdbuf 
/// @return 
int show_mmap(int ** lcdbuf)
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
           
              
            lcd_p[i * 800 + j] = lcdbuf[i][j];

        }
    }

    // 9. 解除映射并关闭文件
    munmap(lcd_p, 800 * 480 * 4);
    // for (int i = 0; i < 480; i++)
    // {
    //     free(lcdbuf[i]);
    //     lcdbuf[i] = NULL;
    // }
    // free(lcdbuf);
    // lcdbuf = NULL;
    close(lcdFd);
    return 1;
}