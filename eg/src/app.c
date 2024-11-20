#include "app.h"

//打开应用
void app_run()
{
    //初始化
    log_init();
    lcd_init();
    touch_init();

    lcd_from_prev_to(lcdBuf,lcdOverBuf);
    bmp_show("./res/bg.bmp",0,0);
    bmp_show("./res/title.bmp",200,200);

    int x,y;
    touch_click(&x,&y);
}

//关闭应用
void app_quit()
{
    lcd_from_prev_to(lcdOverBuf,lcdBuf);

    lcd_destroy();
    touch_destroy();
    log_destroy();
}
