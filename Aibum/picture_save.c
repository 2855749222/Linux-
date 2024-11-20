#include "include/picture_save.h"

int show_save_pic(char * path)
{
    int **lcdbuf = load_bmp_as_argb(path);
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
            if(i >= 25 && i < 455 && j >= 50 && j < 750)
            lcd_p[i * 800 + j] = lcdbuf[i-25][j-50];

        }
    }
    munmap(lcd_p, 800 * 480 * 4);
    close(lcdFd);
    return 1;
}
int main(int argc, char *argv[])
{
   
    char *save_path[] = {"draw_save/0.bmp","draw_save/1.bmp","draw_save/2.bmp","draw_save/3.bmp","draw_save/4.bmp","draw_save/5.bmp","draw_save/6.bmp","draw_save/7.bmp","draw_save/8.bmp","draw_save/9.bmp"};
    int index=0;
    int **pic = load_bmp_as_argb("draw_save/aim.bmp");
    show_mmap(pic);
    show_save_pic(save_path[(index++)%10]);
    while(1)
    {
        int x, y;
        touch_wait(&x, &y);  
        printf("x:%d y:%d\n", x, y);
        if (x > 700 && y > 50)
        {
            show_save_pic(save_path[(index++)%10]);

        }
        else if (x < 100 && index > 0)
        {
            show_save_pic(save_path[(index--)%10]);
        }
        else if (x > 750 && y < 50)
        {
            return 0;
        }
        
        
        
    }
    // Read the image data

}