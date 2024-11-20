#include "pthread_pool.h"
int main()
{
    P_PPI pthread_pool_inf_p = Pthread_Pool_Init();
    if(pthread_pool_inf_p == (P_PPI)-1)
    {
        printf("线程池初始化失败！\n");
        return -1;
    }

    Add_Task(pthread_pool_inf_p);
   
    return 0;
}