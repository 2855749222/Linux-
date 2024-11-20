#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void * show_time1()
{
    while (1)
    {
        printf("time is \n");
    }
}
int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, show_time1, NULL);
    int i = 0;
    while (i<5)
    {
        printf("hello\n");
        i++;
    }
    return 0;
}