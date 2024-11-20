#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <math.h>
#include <linux/input.h>

/*

    21    struct input_event {
    22        struct timeval time;//事件发生的时间
    23        __u16 type;//事件的类型   -> 鼠标/键盘/触摸屏
    24        __u16 code; //事件的编码   -> 对事件进一步的描述  左键/A键/x轴
    25        __s32 value;//事件的值
    26    };


手指按下去
type:3, code:0, value:411
type:3, code:1, value:265

type:1, code:330, value:1
type:0, code:0, value:0

手指离开
type:1, code:330, value:0
type:0, code:0, value:0

#define EV_SYN 			0x00    //同步事件

#define EV_KEY			0x01    //按键事件   type==1
#define BTN_TOUCH		0x14a   //按键       code==330  value:1触摸 0离开


#define EV_ABS			0x03    //绝对坐标事件 type==3
#define ABS_X			0x00    // x轴的坐标  code==0   value==411
#define ABS_Y			0x01    // y轴坐标    code==1   value==265


触摸移动（右）

type:3, code:0, value:196
type:3, code:1, value:233
type:1, code:330, value:1
type:0, code:0, value:0

type:3, code:0, value:202
type:0, code:0, value:0

type:3, code:0, value:207
type:3, code:1, value:235
type:0, code:0, value:0

type:3, code:0, value:212
type:0, code:0, value:0

type:3, code:0, value:219
type:3, code:1, value:237
type:0, code:0, value:0

type:3, code:0, value:225
type:0, code:0, value:0

type:3, code:0, value:230
type:3, code:1, value:239
type:0, code:0, value:0

type:3, code:0, value:235
type:0, code:0, value:0

type:3, code:0, value:239
type:3, code:1, value:241
type:0, code:0, value:0

type:3, code:0, value:243
type:0, code:0, value:0

type:3, code:0, value:247
type:0, code:0, value:0

type:1, code:330, value:0
type:0, code:0, value:0

 */

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int get_direction()
{
    int sx = -1, sy = -1;
    int cx = -1, cy = -1; // 初始值是-1
    int touch_fd = open("/dev/input/event0", O_RDWR);
    if (touch_fd < 0)
    {
        printf("open touch failed\n");
        return -1;
    }
    // printf("open touch success\n");

    struct input_event touch_event;
    while (1)
    {
        // bzero(&touch_event, sizeof(struct input_event));
        int read_ret = read(touch_fd, &touch_event, sizeof(struct input_event));
        // printf("%d %d %d\n", touch_event.type, touch_event.code, touch_event.value);
        if (read_ret < 0)
        {
            perror("read touch failed\n");
            return -1;
        }

        if (touch_event.type == EV_ABS)
        {
            if (touch_event.code == ABS_X)
            {
                cx = touch_event.value * 800 / 1024; // 黑色板子
            }
            else if (touch_event.code == ABS_Y)
            {
                cy = touch_event.value * 480 / 600;
            }
        }

        // 按下
        if (touch_event.type == EV_KEY && touch_event.code == BTN_TOUCH && touch_event.value == 1)
        {
            sx = cx;
            sy = cy;
            // printf("start sx:%d sy:%d cx:%d cy:%d\n", sx, sy, cx, cy);
        }

        // 松手
        if (touch_event.type == EV_KEY && touch_event.code == BTN_TOUCH && touch_event.value == 0)
        {
            if (sx != cx || sy != cy) // 根据你的板子实际情况
            {
                int dir_h = -1;
                int dir_v = -1;
                // printf("end sx:%d sy:%d cx:%d cy:%d\n", sx, sy, cx, cy);

                if (abs(cx - sx) > 100)
                {
                    if (cx > sx)
                    {
                        // return RIGHT;
                        dir_h = RIGHT;
                    }
                    else if (cx < sx)
                    {
                        // return LEFT;
                        dir_h = LEFT;
                    }
                }

                if (abs(cy - sy) > 100)
                {
                    if (cy > sy)
                    {
                        // return DOWN;
                        dir_v = DOWN;
                    }
                    else if (cy < sy)
                    {
                        // return UP;
                        dir_v = UP;
                    }
                }

                // return dir;
                if (abs(cx - sx) > abs(cy - sy))
                {
                    return dir_h;
                }
                else if (abs(cx - sx) < abs(cy - sy))
                {
                    return dir_v;
                }
            }

            return -1;
        }
    }

    close(touch_fd);
}
int main()
{
    while (1)
    {
        int dir = get_direction();
        switch (dir)
        {
        case LEFT:
            printf("left\n");
            break;
        case RIGHT:
            printf("right\n");
            break;

        case UP:
            printf("up\n");
            break;
        case DOWN:
            printf("down\n");
            break;

        case -1:
            printf("未识别\n");
            break;
        }
    }
    return 0;
}