#include <stdio.h>
int main()
{
    char *fiename = "text.txt";
    FILE * fd = fopen(fiename,"r");
    if(fd == NULL)
    {
        perror("fd:");
    }

    char c = fgetc(fd);

    while(c != EOF)
    {
        printf("%c",c);
        c = fgetc(fd);
    }
    printf("\n");
    fclose(fd); 
}