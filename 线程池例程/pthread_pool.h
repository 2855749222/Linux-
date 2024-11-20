#ifndef PTHREAD_POOL_H_
#define PTHREAD_POOL_H_
#include <stdio.h>
#include <stdlib.h>//malloc
#include <string.h> // memset
#include <unistd.h> //sleep
#include <pthread.h>
#include <stdbool.h>

#define PTHREAD_MAX_NUM 5000 //线程的总数
struct task_list;


typedef struct pthread_pool_inf
{
    pthread_cond_t cond;//条件变量

    pthread_mutex_t mutex;//互斥锁
    pthread_t dog_id[PTHREAD_MAX_NUM];//存放劳动线程ID的数组

    pthread_t monitor_id;//实时输出任务和线程的情况的线程ID
    
    int task_num;    //任务的数量
    int pthread_sum; //线程的总数
    int sleeping_num;//在睡觉的线程
    int working_num; //工作的线程
    int running_num; //醒的线程 

    int destroy_mask;   
    
    struct task_list * task_head;//任务链表头节点

}PPI,* P_PPI;


//任务链表结点类型 = 数据域（函数指针变量--实现多任务分配） + 指针域（前驱+后继） 
struct task_list
{
    void * (* task_p)(void * arg);
    char work[50];//工作描述
    int  time;//工作时间片
    struct task_list * next, * prev;
};

P_PPI  Pthread_Pool_Init();
void * Pthread_Pool_Ctrl_Man(void * arg);
void * Monitor_Task(void * arg);
struct task_list * Create_Task_Node();
void * Do_Task(void * arg);
struct task_list * Get_Task_Node(P_PPI pthread_pool_inf_p);
bool   Add_Task(P_PPI pthread_pool_inf_p);
bool   Add_Task_Node(P_PPI pthread_pool_inf_p,const char * work,int time);

#endif