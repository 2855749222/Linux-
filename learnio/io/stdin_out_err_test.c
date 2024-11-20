#include <stdio.h>
#include <stdlib.h>

int main()
{
    char * ch = malloc(100);

    //stdin :
    fgets(ch,100,stdin);

    printf("nihao: %s",ch);

    fputs(ch,stdout);

    fputs(ch,stderr);

}