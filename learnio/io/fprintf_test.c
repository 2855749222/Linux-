#include <stdio.h>
int main()
{
    char *fiename = "text.txt";
    FILE * fd = fopen(fiename,"a+");
    if(fd == NULL)
    {
        perror("fd:");
    }
    char * name = "loqixi";
    int fprintfR = fprintf(fd,",i love you %s",name);

    if(fprintfR == EOF)
    {
        printf("error");
    }
    else
    {
        printf("success:%d\n",fprintfR);
    }
    fclose(fd);
}