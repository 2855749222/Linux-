#include "pthread_pool.h"

P_PPI Pthread_Pool_Init()
{
    P_PPI pthread_pool_inf_p = (P_PPI)malloc(sizeof(PPI));
    if(pthread_pool_inf_p == (P_PPI)NULL)
    {
        perror("malloc ...");
        return (P_PPI)-1;
    }

    memset(pthread_pool_inf_p,0,sizeof(PPI));

     if(pthread_cond_init(&pthread_pool_inf_p->cond,NULL) != 0)
    {
        perror("pthread_cond_init ...");
        return (P_PPI)-1;
    }

    if(pthread_mutex_init(&pthread_pool_inf_p->mutex,NULL) != 0)
    {
        perror("pthread_mutex_init ...");
        return (P_PPI)-1;
    }

    pthread_pool_inf_p->task_num    = 0;
    pthread_pool_inf_p->pthread_sum = 0;
    pthread_pool_inf_p->working_num = 0;
    pthread_pool_inf_p->running_num = 0;
    pthread_pool_inf_p->sleeping_num= 0;
    pthread_pool_inf_p->destroy_mask= 0;

    
    if(pthread_create(&pthread_pool_inf_p->monitor_id,NULL,Monitor_Task,(void *)pthread_pool_inf_p) != 0)
    {
        perror("pthread_create ...");
        return (P_PPI)-1;
    }
    

    if((pthread_pool_inf_p->task_head = Create_Task_Node()) == (struct task_list *)-1)
    {
        printf("创建任务链表头失败！\n");
        return (P_PPI)-1;
    }

    for(int pthread_num=0; pthread_num<PTHREAD_MAX_NUM; pthread_num++)
    {
        if(pthread_create(&pthread_pool_inf_p->dog_id[pthread_num],NULL,Pthread_Pool_Ctrl_Man,(void *)pthread_pool_inf_p) != 0)
        {
            perror("pthread_create");
            return (P_PPI)-1;
        }
        pthread_mutex_lock(&pthread_pool_inf_p->mutex);//上锁
        pthread_pool_inf_p->pthread_sum++;//线程数+1
        pthread_pool_inf_p->running_num++;//醒数+1
        pthread_mutex_unlock(&pthread_pool_inf_p->mutex);//解锁
        
    }
    

    return pthread_pool_inf_p;
}


void * Pthread_Pool_Ctrl_Man(void * arg)
{
    P_PPI pthread_pool_inf_p = (P_PPI)arg;

    while(1)
    {   
        pthread_mutex_lock(&pthread_pool_inf_p->mutex);//上锁
        if(pthread_pool_inf_p->task_head->next == pthread_pool_inf_p->task_head)//判断是不是没有任务
        {
            pthread_pool_inf_p->sleeping_num++;
            pthread_pool_inf_p->running_num--;
            pthread_cond_wait(&pthread_pool_inf_p->cond,&pthread_pool_inf_p->mutex);
            pthread_pool_inf_p->sleeping_num--;
            pthread_pool_inf_p->running_num++;
        }
        else//有任务
        {   
            struct task_list * task_node = Get_Task_Node(pthread_pool_inf_p);//取任务 -- 尾删除结点
            if(task_node == (struct task_list *)-1)
            {
                printf("获取任务结点失败！\n");
                pthread_exit((void *)-1);
            }
            pthread_mutex_unlock(&pthread_pool_inf_p->mutex);//解锁
            //执行任务（并发）
            task_node->task_p((void *)task_node); //回调函数执行任务函数
            free(task_node);
            pthread_mutex_lock(&pthread_pool_inf_p->mutex);//上锁
            pthread_pool_inf_p->working_num--;  
        }

        pthread_mutex_unlock(&pthread_pool_inf_p->mutex);//解锁
    }

    pthread_exit((void *)0);
}


struct task_list * Create_Task_Node()
{
    struct task_list * new_node = (struct task_list *)malloc(sizeof(struct task_list));
    if(new_node == (struct task_list *)NULL)
    {
        perror("malloc ...");
        return (struct task_list *)-1;
    }

    memset(new_node,0,sizeof(struct task_list));

    new_node->next = new_node;
    new_node->prev = new_node;

    return new_node;
}


struct task_list * Get_Task_Node(P_PPI pthread_pool_inf_p) //尾删除
{
    if(pthread_pool_inf_p->task_head == (struct task_list *)NULL)//判断头节点异不异常
    {
        printf("头节点异常！\n");
        return (struct task_list *)-1;
    }

    struct task_list * task_node = pthread_pool_inf_p->task_head->prev;

    task_node->next->prev = task_node->prev;
    task_node->prev->next = task_node->next;
    task_node->next = (struct task_list *)NULL;
    task_node->prev = (struct task_list *)NULL;

    pthread_pool_inf_p->task_num--;
    pthread_pool_inf_p->working_num++;
    return task_node;
}


bool   Add_Task(P_PPI pthread_pool_inf_p)
{
    int select_num;
    while(1)
    {
        printf("工地多任务分配多并发系统！\n");
        printf("1、打螺丝\n");
        printf("2、搬砖\n");
        printf("3、合水泥\n");
        printf("4、开挖掘机\n");
        printf("5、唤醒线程取任务！\n");
        printf("6、退出多任务分配多并发系统！\n");
        scanf("%d",&select_num);

        switch(select_num)
        {
            case 1: 
            
            if(Add_Task_Node(pthread_pool_inf_p,"打螺丝",10) == false)
            {
                printf("添加打螺丝任务失败！\n");
                return false;
            }
            break;


            case 2: 
            if(Add_Task_Node(pthread_pool_inf_p,"搬砖",8) == false)
            {
                printf("添加搬砖任务失败！\n");
                return false;
            }
            break;


            case 3: 
            if(Add_Task_Node(pthread_pool_inf_p,"合水泥",20) == false)
            {
                printf("添加合水泥任务失败！\n");
                return false;
            }
            break;
            

            case 4: 
            if(Add_Task_Node(pthread_pool_inf_p,"开挖掘机",15) == false)
            {
                printf("添加开挖掘机任务失败！\n");
                return false;
            }
            break;

            case 5: pthread_cond_broadcast(&pthread_pool_inf_p->cond);break;

            case 6: goto exit;

            default: printf("没有该任务！\n");break;
        }

        //唤醒线程
        
    }

    exit:
    return true;
}



bool  Add_Task_Node(P_PPI pthread_pool_inf_p,const char * work,int time)
{

    //创建一个新的任务结点，把工作描述和时间片存储进去
    struct task_list * new_node = Create_Task_Node();
    if(new_node == (struct task_list *) NULL)
    {
        printf("创建新的任务结点失败！\n");
        return false;
    }

    strcpy(new_node->work,work);
    new_node->time = time;
    new_node->task_p = Do_Task;

    pthread_mutex_lock(&pthread_pool_inf_p->mutex);//上锁
    //进行头插法
    new_node->next                            = pthread_pool_inf_p->task_head->next;
    pthread_pool_inf_p->task_head->next->prev = new_node;

    new_node->prev                            =  pthread_pool_inf_p->task_head;
    pthread_pool_inf_p->task_head->next       = new_node;

    //任务数+1
    pthread_pool_inf_p->task_num++;

    pthread_mutex_unlock(&pthread_pool_inf_p->mutex);//解锁

    return true;
}


void * Do_Task(void * arg)
{
    struct task_list * take_node = (struct task_list *)arg;
    for(int time=0; time<take_node->time; time++)
    {
        printf("我在%s，剩余%d\n",take_node->work,take_node->time-(time+1));
        sleep(1);
    }
}


void * Monitor_Task(void * arg)
{
    P_PPI pthread_pool_inf_p = (P_PPI)arg;
    while(1)
    {
        
        sleep(1);
        pthread_mutex_lock(&pthread_pool_inf_p->mutex);
        printf("剩余任务数：%d----线程总数：%d----正在工作：%d----正在休眠：%d----就绪数：%d\n",
            pthread_pool_inf_p->task_num,
            pthread_pool_inf_p->pthread_sum,
            pthread_pool_inf_p->working_num,
            pthread_pool_inf_p->sleeping_num,
            pthread_pool_inf_p->running_num);
        pthread_mutex_unlock(&pthread_pool_inf_p->mutex);

    }

    pthread_exit((void *)0);
}