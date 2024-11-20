#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char * name = "ludi";
    printf("in exit, my name is %s, my pid : %d , my father pid : %d\n",name,getpid(),getppid());

    char * args[] = {"/learnio/io/erlou",name,NULL};
    char * envp[] = {"PATH=/learnio/io",NULL};
    int re = execve(args[0],args,NULL);
    if(re == -1)
    {
        printf("no to room\n");
        return -1;
    }
    return 0;
}