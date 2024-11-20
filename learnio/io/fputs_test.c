#include <stdio.h>
int main()
{
    char *fiename = "text.txt";
    FILE * fd = fopen(fiename,"a+");
    if(fd == NULL)
    {
        perror("fd:");
    }

    int putsR = fputs("world",fd);

    if(putsR == EOF)
    {
        printf("error");
    }
    else
    {
        printf("success:%d\n",putsR);
    }
    fclose(fd);
}