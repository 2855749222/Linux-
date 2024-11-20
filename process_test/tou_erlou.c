#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char * argv[])
{
    if(argc < 2)
    {
        printf("file count < 2\n");
        return 1;
    }
    printf("in my roon ,my name is %s ,my pid is %d,my father pid is %d.\n",argv[1],getpid(),getppid());
    sleep(100);
    return 0;
}