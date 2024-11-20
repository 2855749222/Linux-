#ifndef __LCD_H
#define __LCD_H


#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/mman.h>
#include<linux/fb.h>
#include<sys/ioctl.h>
#include <stdlib.h>
#include "log.h"

int lcdFd;
int (*lcdBuf)[800];         //用于映射lcd到内存中
int (*lcdTempBuf)[800];     //用于保存记录lcd关键点显示的内容
int (*lcdOverBuf)[800];     //用于关闭程序时恢复打开程序前lcd显示的内容
int lcdWidth;
int lcdHeight;
struct fb_var_screeninfo lcdVarInfo;

//将lcd的内容显示为prev的内容
#define lcd_from_prev_to(prev,to)   do  \
                                    {   \
                                        for(int y = 0; y < lcdHeight; y++)  \
                                        {   \
                                            for(int x = 0; x < lcdWidth; x++)   \
                                            {   \
                                                to[y][x] = prev[y][x];  \
                                            }   \
                                        }   \
                                    } while (0);

//初始化液晶屏
void lcd_init();

//液晶屏销毁
void lcd_destroy();

#endif