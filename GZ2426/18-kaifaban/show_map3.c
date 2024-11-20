#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
int main()
{
    FILE *fp;
    fp = fopen("1.bmp", "r");
    if (fp == NULL)
    {
        printf("打开文件失败\n");
        exit(0);
    }
    fseek(fp, 54, SEEK_SET);
    unsigned char buf[200 * 100 * 3];
    fread(buf, 1, 200 * 100 * 3, fp); // 读取图像数据

    int fd = open("/dev/fb0", O_RDWR);
    if (fd == -1)
    {
        printf("打开设备失败\n");
        exit(0);
    }
    unsigned char *p = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
        printf("映射失败\n");
        exit(0);
    }
    //
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if (i < 100 && j < 200)
            {
                p[i * 800 * 4 + j * 4] = 0x00;
                p[i * 800 * 4 + j * 4 + 1] = 0x00;
                p[i * 800 * 4 + j * 4 + 2] = 0x00;
                p[i * 800 * 4 + j * 4 + 3] = 0;
            }
        }
    }
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if (i < 100 && j < 200)
            {
                p[i * 800 * 4 + j * 4] = buf[(100 - i) * 200 * 3 + j * 3];
                p[i * 800 * 4 + j * 4 + 1] = buf[(100 - i) * 200 * 3 + j * 3 + 1];
                p[i * 800 * 4 + j * 4 + 2] = buf[(100 - i) * 200 * 3 + j * 3 + 2];
                p[i * 800 * 4 + j * 4 + 3] = 0;
            }
        }
    }
    write(fd, p, 800 * 480 * 4);
    munmap(p, 800 * 480 * 4);

    close(fd);
    fclose(fp);
}