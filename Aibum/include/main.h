#ifndef MAIN_H
#define MAIN_H

#include "head.h"
#include "get_touch_index.h"
#include "load_bmp_as_argb.h"
#include "show_mmap.h"
#include "show_time.h"

int tiem_status;
int playonescore;
int playtwoscore;
#define ROSE 1
#define SIZE 100
struct msgbuf
{
    long msgtype;
    char msgtext[SIZE];
};
#endif
