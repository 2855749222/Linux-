#include <stdio.h>
#include <stdlib.h> //malloc
#include <string.h> // memset
#include <unistd.h> //sleep
#include <pthread.h>
#include <stdbool.h>

#define DOG_MAX_NUM 10 // 狗的总数

typedef struct Feed_Dog_Foods_Demo
{
    pthread_cond_t cond; // 条件变量

    pthread_mutex_t mutex;         // 互斥锁
    pthread_t dog_id[DOG_MAX_NUM]; // 存放狗ID的数组

    pthread_t monitor_id; // 实时输出狗和狗粮的情况的线程ID

    int dog_foods;    // 狗粮的数量
    int dog_sum;      // 狗的总数
    int sleeping_num; // 在睡觉的狗
    int eating_num;   // 吃的狗
    int running_num;  // 醒的狗
    int destroy_mask; //标准位

} FD, *P_FD;

P_FD Demo_Init(); // 例程初始化 = 创建结构体堆空间+初始化条件变量+初始化互斥锁+初始化各个数据值+创建100条线程+创建1条线程
void *Manage_Task(void *arg);
void *Monitor_Task(void *arg);
void *Monitor_Task(void *arg)
{
    P_FD inf_heap_p = (P_FD)arg;
    while (!inf_heap_p->destroy_mask)
    {
        sleep(1);
        printf("剩余狗粮数：%d----狗数：%d----正在吃：%d----正在睡：%d----醒：%d\n",
               inf_heap_p->dog_foods,
               inf_heap_p->dog_sum,
               inf_heap_p->eating_num,
               inf_heap_p->sleeping_num,
               inf_heap_p->running_num);
    }
}
void *Manage_Task(void *arg)
{
    P_FD inf_heap_p = (P_FD)arg;

    while (!inf_heap_p->destroy_mask)
    {
        pthread_mutex_lock(&inf_heap_p->mutex); // 上锁
        if (inf_heap_p->dog_foods < 3)
        {
            printf("我是%ld的狗线程，准备休眠！\n", pthread_self());
            inf_heap_p->sleeping_num++;
            inf_heap_p->running_num--;
            pthread_cond_wait(&inf_heap_p->cond, &inf_heap_p->mutex);
            inf_heap_p->sleeping_num--;
            inf_heap_p->running_num++;
        }
        else
        {
            inf_heap_p->dog_foods -= 3;
            inf_heap_p->eating_num++;
            pthread_mutex_unlock(&inf_heap_p->mutex); // 解锁
            printf("我是%ld的狗线程，在吃狗粮！\n", pthread_self());
            sleep(3);
            printf("我是%ld的狗线程，吃完了！\n", pthread_self());
            pthread_mutex_lock(&inf_heap_p->mutex);//上锁
            inf_heap_p->eating_num--;
        }

        pthread_mutex_unlock(&inf_heap_p->mutex); // 解锁
    }
}

P_FD Demo_Init()
{
    P_FD inf_head_p = (P_FD)malloc(sizeof(FD));
    if (inf_head_p == (P_FD)NULL)
    {
        perror("malloc ...");
        return (P_FD)-1;
    }

    memset(inf_head_p, 0, sizeof(FD));

    if (pthread_cond_init(&inf_head_p->cond, NULL) != 0)
    {
        perror("pthread_cond_init ...");
        return (P_FD)-1;
    }

    if (pthread_mutex_init(&inf_head_p->mutex, NULL) != 0)
    {
        perror("pthread_mutex_init ...");
        return (P_FD)-1;
    }
    inf_head_p->destroy_mask = 0;
    inf_head_p->dog_foods = 0;
    inf_head_p->dog_sum = 0;
    inf_head_p->eating_num = 0;
    inf_head_p->running_num = 0;
    inf_head_p->sleeping_num = 0;

    if (pthread_create(&inf_head_p->monitor_id, NULL, Monitor_Task, (void *)inf_head_p) != 0)
    {
        perror("pthread_create ...");
        return (P_FD)-1;
    }
    for (int dognum = 0; dognum < DOG_MAX_NUM; dognum++)
    {
        if (pthread_create(&inf_head_p->dog_id[dognum], NULL, Manage_Task, (void *)inf_head_p) != 0)
        {
            perror("pthread_create");
            return (P_FD)-1;
        }

        pthread_mutex_lock(&inf_head_p->mutex);   // 上锁
        inf_head_p->dog_sum++;                    // 狗数+1
        inf_head_p->running_num++;                // 醒数+1
        pthread_mutex_unlock(&inf_head_p->mutex); // 解锁
    }

    return inf_head_p;
}
bool Make_dog_foods(P_FD inf_heap_p)
{

    while (getchar() != 'W')
    {
        pthread_mutex_lock(&inf_heap_p->mutex); // 上锁
        inf_heap_p->dog_foods += 3;
        pthread_mutex_unlock(&inf_heap_p->mutex); // 解锁
                                                  // 全部唤醒
        if (pthread_cond_broadcast(&inf_heap_p->cond) != 0)
        {
            perror("pthread_cond_broadcast ...");
            return false;
        }
    }

    return true;
}
bool Demo_Free(P_FD inf_heap_p)
{   
    //修改标准位
    inf_heap_p->destroy_mask = 1;
    pthread_cond_broadcast(&inf_heap_p->cond);//全部唤醒

    //回收100条工作线程
    for(int dognum=0; dognum<DOG_MAX_NUM; dognum++)
    {
        if(pthread_join(inf_heap_p->dog_id[dognum],NULL) != 0)
        {
            perror("pthread_join ...");
            return false;
        }
    }


    //回收监工线程
    if(pthread_join(inf_heap_p->monitor_id,NULL) != 0)
    {
        perror("pthread_join ...");
        return false;
    }


    //摧毁互斥锁
    if(pthread_mutex_destroy(&inf_heap_p->mutex) != 0)
    {
        perror("pthread_mutex_destroy ...");
        return false;
    }

    //摧毁条件变量
     if(pthread_cond_destroy(&inf_heap_p->cond) != 0)
    {
        perror("pthread_cond_destroy ...");
        return false;
    }

    //释放inf_heap_p 资源
    free(inf_heap_p);

    return true;
}
int main()
{
    P_FD inf_heap_p = Demo_Init();
    if (inf_heap_p == (P_FD)-1)
    {
        printf("例程初始化失败！\n");
        return -1;
    }
    if (Make_dog_foods(inf_heap_p) == false)
    {
        printf("投递狗粮失败！\n");
        return -1;
    }
    
    if(Demo_Free(inf_heap_p) == false)
    {
        printf("例程结束释放失败！\n");
        return -1;
    }

    return 0;
}