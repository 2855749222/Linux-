#include "../include/get_touch_index.h"
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
         
            *x =  (info.value * 800 *1.0) / 1024;
            // printf("1 x = %d\n", *x);   
        }
        //判断是触摸屏事件 而且是Y轴事件
        if(info.type == EV_ABS && info.code == ABS_Y)
        {
      
    
            *y =  (info.value * 480 *1.0) / 600;
            // printf("1 y = %d\n",*y);   
        }
        //3 将触摸屏的坐标打印出来
        //printf("type:%d, code:%d, value:%d\n", info.type, info.code, info.value);
        //压力事件 并且是触摸屏的压力事件，松开的时候
        if(info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 0)
        {
            //黑色屏幕的开发板 坐标范围：x(0-1024)   y(0-600)
            //蓝色屏幕的开发板 坐标范围：x(0-800)   y(0-480)
            printf("*x = %d, *y = %d\n", *x, *y);   
            break;        
        }
    }
    
    //4 关闭触摸屏文件
    close(tsFd);
    return 0;
}