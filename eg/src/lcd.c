#include "lcd.h"

//初始化液晶屏
void lcd_init()
{
    lcdFd = open("/dev/fb0",O_RDWR);
    if(lcdFd == -1)
    {
        log_error("open lcd error");
        return;
    }

    if(ioctl(lcdFd,FBIOGET_VSCREENINFO,&lcdVarInfo) != 0)
    {
        perror("获取lcd信息失败");
        log_error("get lcd info failed");
        close(lcdFd);
        return;
    }

    lcdWidth = lcdVarInfo.xres;
    lcdHeight = lcdVarInfo.yres;

    lcdBuf = (int(*)[lcdWidth])mmap(NULL,
                                        lcdWidth * lcdHeight * sizeof(int),
                                        PROT_READ | PROT_WRITE,
                                        MAP_SHARED,
                                        lcdFd,
                                        0);
    if(lcdBuf == MAP_FAILED)
    {
        log_error("mmap lcd failed");
        return;
    }

    lcdTempBuf = (int(*)[lcdWidth])malloc(lcdWidth * lcdHeight * sizeof(int));
    if(lcdTempBuf == NULL)
    {
        perror("tempBuf malloc error");
        log_error("tempBuf malloc error");
        return;
    }

    lcdOverBuf = (int(*)[lcdWidth])malloc(lcdWidth * lcdHeight * sizeof(int));
    if(lcdOverBuf == NULL)
    {
        perror("tempBuf malloc error");
        log_error("tempBuf malloc error");
        return;
    }
    
    log_debug("lcd init completed");
}

//液晶屏销毁
void lcd_destroy()
{
    munmap(lcdBuf,lcdWidth * lcdHeight * sizeof(int));
    free(lcdTempBuf);
    free(lcdOverBuf);
    close(lcdFd);
    
    log_debug("lcd destroy completed");
}
