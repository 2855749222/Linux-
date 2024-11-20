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

#include <pthread.h>

/*
编译的时候  加上  -lpthread

int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);
// 参数一 线程号  参数二线程属性 NULL  参数三函数的指针 线程里面要运行的函数   参数四 传递给参数三这个函数的参数
 */

void show_time()
{
    while (1)
    {
        time_t ret = time(NULL);
        printf("当前时间 %s", ctime(&ret));
        sleep(1);
    }
}

// int main()
// {

//     while (1)
//     {
//         printf("触屏侦听\n");
//         sleep(1);
//     }
//     show_time();

//     return 0;
// }

int main()
{

    pthread_t tid;
    pthread_create(&tid, NULL, show_time, NULL);

    while (1)
    {
        printf("触屏侦听\n");
        sleep(1);
    }

    return 0;
}
// /*
// 时间显示需要 死循环 定时器
// 触屏侦听需要 死循环 触摸屏
// 轮播图 需要定时器 死循环 图片




 