#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include "input-event-codes.h"
#include <linux/input.h>//触摸屏的头文件
// struct input_event
// {
//     struct timeval time; // 事件发生的时间
//     int type;          // 事件的类型   -> 鼠标/键盘/触摸屏
//     int code;          // 事件的编码   -> 对事件进一步的描述  左键/A键/x轴
//     int value;         // 事件的值
// };

int touch_wait(int *x, int *y)
{
    //1 打开触摸屏设备文件  touch sreen
    int tsFd = open("/dev/input/event0", O_RDWR);
    if(tsFd == -1)
    {
        perror("open touch error");
        return -1;
    }
    //2 读取触摸屏设备的坐标
    while(1)
    {
        struct input_event info;
        read(tsFd,&info,sizeof(info));
        
        //判断是触摸屏事件 而且是X轴事件
        if(info.type == EV_ABS && info.code == ABS_X)
        {
            *x = info.value;
            int *X = x;
            *x =  ((*x) * 800 *1.0) / 1024;
            printf("1 x = %d\n", *x);   
        }
        //判断是触摸屏事件 而且是Y轴事件
        if(info.type == EV_ABS && info.code == ABS_Y)
        {
            *y = info.value;
            int *Y = y;
            *y =  ((*y) * 480 *1.0) / 600;
            printf("1 y = %d\n",*y);   
        }
        //3 将触摸屏的坐标打印出来
        //printf("type:%d, code:%d, value:%d\n", info.type, info.code, info.value);
        //压力事件 并且是触摸屏的压力事件，松开的时候
        if(info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 0)
        {
            //黑色屏幕的开发板 坐标范围：x(0-1024)   y(0-600)
            //蓝色屏幕的开发板 坐标范围：x(0-800)   y(0-480)
           
          
            printf("x = %d, y = %d\n", *x, *y);   
            break;        
        }
    }


    //4 关闭触摸屏文件
    close(tsFd);
}


int main()
{
    int x,y;
    while(1)
    {
        touch_wait(&x,&y);

        if(x>0 && x<800/2 )
        {
            printf("left\n");
        }
        else if (x>800/2 && x<800)
        {
            printf("right\n");
        }
        
    }
}
