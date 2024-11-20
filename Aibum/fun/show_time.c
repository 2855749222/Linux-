#include "../include/show_time.h"
void *show_time()
{
    char buf[50] = {0};
    // time_t ret = time(NULL);
    // struct tm *localresult = localtime(&ret);

    while (tiem_status)
    {
        time_t ret = time(NULL);
        struct tm * localresult = localtime(&ret);
        sprintf(buf, "%02d:%02d:%02d %d/%02d/%02d", localresult->tm_hour, localresult->tm_min, localresult->tm_sec, localresult->tm_year + 1900, localresult->tm_mon + 1, localresult->tm_mday ); //将时间格式化
        bit(buf,695, 450);
        printf("%s",buf);
        //usleep(500000); //0.5s
    }
    return NULL;
}
