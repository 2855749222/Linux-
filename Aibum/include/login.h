#ifndef LOGIN_H
#define LOGIN_H

#include "head.h"
#include "get_touch_index.h"
#include "load_bmp_as_argb.h"
#include "show_mmap.h"
#include "font.h"
typedef struct array
{
    int index;
    char *data[30];
} array;
array *person, *passwd, *Reper,*Repwd;
void showfont(array *n, int pox, int poy,int width,int hight)//显示字体
{
    char buf[30];
    memset(buf, 0, 30);
    if (n == passwd)
    {
       for (int i = 0; i < n->index; i++)
        {
            buf[i] = 'x';
        }
    }
    else
    {
         for (int i = 0; i < n->index; i++)
        {
            buf[i] = n->data[i];
        }
        
    }
     

    printf("\n%s", buf);
    struct LcdDevice *lcd = init_lcd("/dev/fb0");
    // 初始化Lcd
    font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

    // 字体大小的设置
    fontSetSize(f, 20);

    // 创建一个画板（点阵图）
    bitmap *bm = createBitmapWithInit(width, hight, 4, getColor(0, 212, 215, 218)); // 也可使用createBitmap函数，改变画板颜色
                                                                               // getColor(0, 255, 0, 0)  ABGR
                                                                               // bitmap *bm = createBitmap(288, 100, 4);
    // 将字体写到点阵图上
    fontPrint(f, bm, 5, 5, buf, getColor(0, 0, 0, 0), 200);

    // 把字体框输出到LCD屏幕上
    show_font_to_lcd(lcd->mp, pox, poy, bm);
    // 关闭字体，关闭画板
    fontUnload(f);
    destroyBitmap(bm);
}
void show_error_login(char *buf,int pox, int poy)
{
 
    struct LcdDevice *lcd = init_lcd("/dev/fb0");
    // 初始化Lcd
    font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

    // 字体大小的设置
    fontSetSize(f, 20);

    // 创建一个画板（点阵图）
    bitmap *bm = createBitmapWithInit(100, 25, 4, getColor(0, 212, 215, 218)); // 也可使用createBitmap函数，改变画板颜色
                                                                               // getColor(0, 255, 0, 0)  ABGR
                                                                               // bitmap *bm = createBitmap(288, 100, 4);
    // 将字体写到点阵图上
    fontPrint(f, bm, 5, 5, buf, getColor(0, 0, 0, 255), 200);

    // 把字体框输出到LCD屏幕上
    show_font_to_lcd(lcd->mp, pox, poy, bm);
    // 关闭字体，关闭画板
    fontUnload(f);
    destroyBitmap(bm);
}
int status = 1;
int Restatus = 1;
int **logininput;
int **Registd;
#endif
