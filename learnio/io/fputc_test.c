#include <stdio.h>
int main()
{
    char *fiename = "text.txt";
    FILE * fd = fopen(fiename,"a+");
    if(fd == NULL)
    {
        perror("fd:");
    }

    int putcR = fputc('o',fd);

    if(putcR == EOF)
    {
        printf("error");
    }
    else
    {
        printf("success:%d\n",putcR);
    }
    fclose(fd);
}