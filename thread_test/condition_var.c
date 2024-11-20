#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

// 初始化锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 初始化条件变量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)
{
     // 获取互斥锁 拿不到等
    pthread_mutex_lock(&mutex);
    int item = 1;
    while (1)
    {
        sleep(1);
       
        // 如果缓冲区满，等消费者读取
        while (count == BUFFER_SIZE)
        {
            printf("满了\n");
            // 暂停线程 等待唤醒
            pthread_cond_wait(&cond, &mutex);
        }
        // 能到这里说明缓冲区不满 可以写一个
        buffer[count++] = item++;
        printf("白月光发送一个幸运数字%d\n", buffer[count - 1]);
        // 通知消费者可以消费数据了
        // 唤醒消费者 同时解锁
        pthread_cond_signal(&cond);
       
      
    }
     pthread_mutex_unlock(&mutex);
    // 释放锁
   
}

void *consumer(void *arg)
{
    // 获取互斥锁 拿不到等
    pthread_mutex_lock(&mutex);
    while (1)
    {
        sleep(1);
       
        // 如果缓冲区为空，则等待生产者生产数据
        while (count == 0) 
        {
            printf("空的\n");
            // 暂停线程 等待唤醒
            pthread_cond_wait(&cond, &mutex);
        }
        printf("我收到了幸运数字 %d\n", buffer[--count]);
        // 通知生产者可以发送数据了
        // 唤醒生产者 同时解锁
        pthread_cond_signal(&cond);
       
    }
     pthread_mutex_unlock(&mutex);
    // 释放锁
   
}
int main()
{
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    return 0;
}