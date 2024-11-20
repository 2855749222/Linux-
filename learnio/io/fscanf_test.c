#include <stdio.h>
int main()
{
    char *fiename = "text.txt1";
    FILE * fd = fopen(fiename,"r");
    if(fd == NULL)
    {
        perror("fd:");
    }

    char name[500];
    int age;
    char wife[50];
    char xx[50];
    int scanfR;
    fscanf(fd,"! %s !",name);
    printf("%s!",name);
  
   
    // while((scanfR = fscanf(fd,"%s %d %s\n",name,&age,wife)) != EOF)
    // {
    //     printf("read %d num\n",scanfR);
    //     printf("%s in %d age , love to %s\n",name,age,wife);
        
    // }
    
    fclose(fd);
}