#include <stdio.h>

int main()
{
    FILE * stdin = fopen("text.txt","r+");
    int ch;
    ch = fgetc(stdin);
    printf("%c\n",ch);

    FILE *fp;
    int ch,count = 0;
    if((fp = fopen(argv[1],"r")) == NULL)
    {
        perror("fopen");
        return -1;
    }
    
    return 0;
}