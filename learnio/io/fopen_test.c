#include <stdio.h>
#include <string.h>
#include <errno.h>
int main()
{
    
    FILE * fp;
    int i = 1; // 初始化 i 为 1，因为至少尝试了一次打开文件
    char *filename = "text.txt1";
    // while ((fp = fopen(filename, "a")) != NULL) // 将赋值和判断合并到一行
    // {
    //     // 关闭文件指针以避免资源泄漏
    //     i++;
    // }
    // printf("%d\n", i);
    fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("fopen:%s", strerror(errno));
        perror("fopen");
        return -1;  
    }
    else
    {  
        printf("111"); 
    }
    fclose(fp);
    return 0;
}