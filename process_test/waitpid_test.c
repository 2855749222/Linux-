#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc,char const *argv[])
{
    int subprocess_status;
    char * name = "old man";
    printf("%s in the exit , pid :%d\n",name,getpid());
    __pid_t pid = fork();
    if(pid == -1)
    {
        printf("error fork");
    }
    else if(pid == 0)
    {
        char *args[] = {"/usr/bin/ping","-c","10","www.baidu.com",NULL};
        printf("new man %d call 10 count\n",getpid());
        int re = execve(args[0],args,NULL);
        if (re == -1)
        {
            printf("no call\n");
            return 1;
        }
    }
    else
    {
        
        printf("%s: %d whait yang man: %d call\n",name,getpid(),pid);
        waitpid(pid,&subprocess_status,0);
        printf("young man status :%d\n",subprocess_status);
    }
    printf("call over\n");
    return 0;
}