#include <stdio.h>
int main()
{
    char *fiename = "text.txt";
    FILE * fd = fopen(fiename,"r");
    if(fd == NULL)
    {
        perror("fd:");
    }
    char buffer[100];
    while(fgets(buffer,6,fd) != NULL)
    {
        printf("%s",buffer);
        printf("*");
    }
    // char c;
    // while ((c = fgetc(fd)) != EOF)
    // {
    //     printf("%c",c);    
    // }
    printf("\n");
    fclose(fd);
    
}