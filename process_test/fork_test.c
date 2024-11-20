#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    printf("curr pid :%d \n",getpid());
    pid_t pid = fork();
    if(pid < 0)
    {
        printf("error\n");
        return 0;
    }else if(pid == 0)
    {
        printf("new pid : %d , old pid : %d\n",getpid(),getppid());

    }else
    {
        printf("old pid : %d . he creat new pid: %d\n",getpid(),pid);
    }
    return 0;
}