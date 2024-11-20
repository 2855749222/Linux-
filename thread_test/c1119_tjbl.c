#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// 初始化锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 初始化条件变量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *pthread_Task(void *arg)
{
    printf("睡觉");
     // 暂停线程 等待唤醒
    if(pthread_cond_wait(&cond,&mutex)!= 0)
    {
        perror("pthread_cond_wait ...");
        pthread_exit((void *)-1);
    }
    printf("醒了");
}
void main()
{
    pthread_t pid;
    pthread_create(&pid, NULL, pthread_Task, NULL);
   

    getchar();

    //唤醒
    pthread_cond_signal(&cond);

    pthread_join(pid, NULL);
}