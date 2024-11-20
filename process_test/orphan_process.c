#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc,char const *argv[])
{
    char * name = "old man";
    printf("%s in the exit , pid :%d\n",name,getpid());
    __pid_t pid = fork();
    if(pid == -1)
    {
        printf("error fork");
    }
    else if(pid == 0)
    {
        char *newname = "young man";
        char *args[] = {"/learnio/io/tou_erlou",newname,NULL};
        int re = execve("/learnio/io/tou_erlou",args,NULL);
        if (re == -1)
        {
            printf("no in my room\n");
            return 1;
        }
    }
    else
    {
        
        printf("%s: %d sets yang man: %d in the room,but he in the curr\n",name,getpid(),pid);
      
    }
    return 0;
}