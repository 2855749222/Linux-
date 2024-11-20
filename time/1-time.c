#include <stdio.h>
#include <time.h>

int main()
{
    time_t tloc;

    time_t ret = time(&tloc);
    printf("time_t: %ld\n", ret);
    printf("time_t: %ld\n", tloc);

    time_t ret1 = time(NULL);
    printf("time_t: %ld\n", ret1); // 1723684244
                                   // 时间戳 1970 0101 00.00.00  UTC世界时  中国时区：东八区 +8.00

    // 返回时间字符串 时区是本地   // 返回的是国际格式  周几 月 日  时:分:秒  年
    printf("ctime: %s\n", ctime(&ret1));

    char buf[255] = {0};
    printf("ctime_r: %s\n", ctime_r(&ret1, buf));
    printf("buf: %s\n", buf);

    // 世界时间结构体
    struct tm *result = gmtime(&ret1);

    printf("%p\n", result);                   // 2024 08 15
    printf("tm_year: %d\n", result->tm_year); // 124  从 1900 年算起至今的年数
    printf("tm_mon: %d\n", result->tm_mon);   // 7  范围从 0-11
    printf("tm_mday: %d\n", result->tm_mday); // 15  目前月份的日数, 范围 01-31
    printf("tm_wday: %d\n", result->tm_wday); // 4  一星期的日数, 从星期一算起, 范围为 0-6(周日是0)

    printf("tm_hour: %d\n", result->tm_hour); // UTC 世界时
    printf("tm_min: %d\n", result->tm_min);   //
    printf("tm_sec: %d\n", result->tm_sec);   //

    // 本地时间结构体
    struct tm *localresult = localtime(&ret1);
    printf("%p\n", localresult);                   // 2024 08 15
    printf("tm_year: %d\n", localresult->tm_year); // 124  从 1900 年算起至今的年数
    printf("tm_mon: %d\n", localresult->tm_mon);   // 7  范围从 0-11
    printf("tm_mday: %d\n", localresult->tm_mday); // 15  目前月份的日数, 范围 01-31
    printf("tm_wday: %d\n", localresult->tm_wday); // 4  一星期的日数, 从星期一算起, 范围为 0-6(周日是0)

    printf("tm_hour: %d\n", localresult->tm_hour); // UTC 世界时
    printf("tm_min: %d\n", localresult->tm_min);   //
    printf("tm_sec: %d\n", localresult->tm_sec);   //

    // 把结构体转换成为字符串 ctime 时区是本地
    printf("asctime(localresult): %s\n", asctime(localresult));
    printf("asctime(result): %s\n", asctime(result));

    return 0;

    // #date 查看时间
    // #date  -s  "2023-08-15 08:00:00" 设置时间
    // # date -R 查看时区
}
