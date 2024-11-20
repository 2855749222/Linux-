#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "font.h"
#include <stdlib.h>
#include <unistd.h>

struct lcd_t
{
    int fd;
    int(*mp);
} lcd_t;

struct lcd_t *lcd_init()
{

    struct lcd_t *lcd = malloc(sizeof(struct lcd_t));

    lcd->fd = open("/dev/fb0", O_RDWR);
    lcd->mp = (int(*))mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd->fd, 0);

    return lcd;
}

int main()
{

    struct lcd_t *lcd = lcd_init();
    printf("%d\n", lcd->fd);

    // =========
    font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");
    // 字体大小的设置
    fontSetSize(f, 38);

    while (1)
    {
        // 创建一个画板（点阵图）
        bitmap *bm = createBitmapWithInit(300, 35, 4, getColor(0, 255, 0, 255)); // 也可使用createBitmap函数，改变画板颜色
        // getColor(0, 255, 0, 0)  ABGR
        // bitmap *bm = createBitmap(288, 100, 4);

        // char bufstr[] = "Hello你好";

        // =============
        time_t ret = time(NULL);
        printf("time_t: %ld\n", ret);
        printf("ctime: %s\n", ctime(&ret));

        // 本地时间结构体
        struct tm *localresult = localtime(&ret);
        printf("%p\n", localresult);                   // 2024 08 15
        printf("tm_year: %d\n", localresult->tm_year); // 124  从 1900 年算起至今的年数
        printf("tm_mon: %d\n", localresult->tm_mon);   // 7  范围从 0-11
        printf("tm_mday: %d\n", localresult->tm_mday); // 15  目前月份的日数, 范围 01-31
        printf("tm_wday: %d\n", localresult->tm_wday); // 4  一星期的日数, 从星期一算起, 范围为 0-6(周日是0)

        printf("tm_hour: %d\n", localresult->tm_hour); // UTC 世界时
        printf("tm_min: %d\n", localresult->tm_min);   //
        printf("tm_sec: %d\n", localresult->tm_sec);   //

        char buf[128] = {0};
        sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d", localresult->tm_year + 1900, localresult->tm_mon + 1, localresult->tm_mday, localresult->tm_hour, localresult->tm_min, localresult->tm_sec);

        printf("buf: %s\n", buf);

        // =============

        // 将字体写到点阵图上  // 注意：颜色的设置要用  getColor(A,B,G,R)
        fontPrint(f, bm, 0, 0, buf, getColor(0, 0, 0, 255), 0);

        // 把字体框输出到LCD屏幕上
        show_font_to_lcd(lcd->mp, 550, 440, bm);

        // // 关闭字体，关闭画板
        // fontUnload(f);
        destroyBitmap(bm);
        sleep(1);
    }

    return 0;
}
