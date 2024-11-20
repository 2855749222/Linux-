#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>
#include <linux/fb.h> 
#include <sys/mman.h>
#include <math.h>

#include <pthread.h>
#include <semaphore.h>

#define WHITE 0x00ffffff      // 白色
#define RED 0x00ff0000        // 红色
#define CYAN 0x0000ffff       // 青色
#define HOTPINK 0x00ff69b4    // 热粉红
#define DEEPPINK 0x00ff1493   // 深粉红
#define ORANGE 0x00ffa500     // 橙色
#define MAGENTA 0x00ff00ff    // 洋红
#define PURPLE 0x00800080     // 紫色
#define BLACK 0x00000000      // 黑色
#define LightYellow4 0x8B8B7A // 浅黄色
#define SpringGreen1 0x00FF7F // 春绿色

#define ROW 480
#define COL 800

struct xy
{
    int x;
    int y;
};

struct xy pos;
sem_t s;
int begin = -1; //判断是否开始画图
int (*lcd_mmap)[800];
int touch_fd,lcd_fd;
int color[]={WHITE,RED,CYAN,HOTPINK,DEEPPINK,ORANGE,MAGENTA,PURPLE,BLACK,LightYellow4,SpringGreen1};




//使用中点画线方法画出pos1和pos2两点间的直线
void drawline(struct xy pos1, struct xy pos2)
{
    int dx = pos2.x - pos1.x;
    int dy = pos2.y - pos1.y;
    int x = pos1.x;
    int y = pos1.y;
    int xend = pos2.x;
    int yend = pos2.y;
    int xstep, ystep;
    int d, d1, d2;
    if (dx >= 0)
        xstep = 1;
    else
    {
        xstep = -1;
        dx = -dx;

    }
    if (dy >= 0)
        ystep = 1;
    else
    {
        ystep = -1;
        dy = -dy;

    }
    if (dx > dy)//横向比重大
    {
        d = 2 * dy - dx;
        d1 = 2 * dy;
        d2 = 2 * (dy - dx);
        while (x != xend)
        {
            if (d < 0)
                d += d1;
            else
            {
                d += d2;
                y += ystep;

            }
            x += xstep;
            // *(lcd_mmap + y * COL + x) = color[0];
            lcd_mmap[y][x] = color[0];//映射画线
            
        }

    }
    else//纵向比重大
    {
        d = 2 * dx - dy;
        d1 = 2 * dx;
        d2 = 2 * (dx - dy);
        while (y != yend)
        {
            if (d < 0)
                d += d1;
            else
            {
                d += d2;
                x += xstep;

            }
            y += ystep;
            // *(lcd_mmap + y * COL + x) = color[0];
            lcd_mmap[y][x] = color[0];//映射画线
        }

    }

}

void *drawLines(void *arg)
{
    // 定义两个xy结构体变量，用于存储坐标
    struct xy pos1 = {0};
    struct xy pos2 = {0};

    // 无限循环
    while(1)
    {
        // 等待信号量s
        sem_wait(&s);
        // 将pos的坐标赋值给pos1
        pos1.x = pos.x;
        pos1.y = pos.y;

        // 无限循环
        while(1)
        {
            // 等待信号量s
            sem_wait(&s);

            // 如果begin为1，则将begin置为0，跳出循环
            if(begin == 1)
            {
                begin = 0;
                break;
            }

            // 绘制直线
            pos2 = pos;

            drawline(pos1, pos2);

            // 存储坐标
        printf("pos.x=%d,pos.y=%d\n",pos.x,pos.y);
        printf("pos1.x=%d,pos1.y=%d\n",pos1.x,pos1.y);
        printf("pos2.x=%d,pos2.y=%d\n",pos2.x,pos2.y);
        printf("------------------------------------------\n");
            pos1 = pos2;
        }
    }
}


int main()
{
    lcd_fd=open("/dev/fb0",O_RDWR);
    touch_fd=open("/dev/input/event0",O_RDONLY);
    lcd_mmap = mmap(NULL,ROW*COL*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd_fd,0);
    bzero(lcd_mmap,ROW*COL*4); //清屏

    sem_init(&s, 0, 0);

    // 创建线程，绘制线条
    pthread_t tid;
    pthread_create(&tid, NULL, drawLines, NULL);

    struct input_event touch_event;
    while(1)
    {
        bzero(&touch_event,sizeof(touch_event));
        read(touch_fd,&touch_event,sizeof(touch_event));
        if(touch_event.type==EV_ABS)
        {
            if(touch_event.code==ABS_X)
            {
                pos.x=touch_event.value*800/1024;
            }
            if(touch_event.code==ABS_Y)
            {
                pos.y=touch_event.value*480/600;
            }
        }
        if(touch_event.type==EV_SYN)
        {
            sem_post(&s);//唤醒绘制线程
        }
        if (touch_event.type == EV_KEY && touch_event.code == BTN_TOUCH && touch_event.value == 0)
        {
            begin = 1;
        }
    }
}





