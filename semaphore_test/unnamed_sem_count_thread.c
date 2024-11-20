#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
 
// 声明两个信号量指针，分别用于表示缓冲区是否为空（empty）和是否为满（full）
sem_t *full;
sem_t *empty;
 
// 声明一个整型变量，作为生产者和消费者之间共享的缓冲区
int shard_num;
 
// 定义一个函数，用于生成一个随机数
int rand_num()
{
    srand(time(NULL)); // 注意：这里每次调用rand_num都会重新初始化随机数种子，这通常是不希望的。
    return rand();
}
 
// 生产者线程函数
void *producer(void *argv)
{
    for (int i = 0; i < 5; i++) // 生产者循环5次
    {
        sem_wait(empty); // 等待缓冲区为空
        printf("\n==========> 第 %d 轮数据传输 <=========\n\n", i + 1);
        sleep(1); // 模拟生产过程的时间消耗
        shard_num = rand_num(); // 生成一个随机数作为数据
        printf("producer has sent data\n");
        sem_post(full); // 通知消费者缓冲区已满
    }
    return NULL;
}
 
// 消费者线程函数
void *consumer(void *argv)
{
    for (int i = 0; i < 5; i++) // 消费者循环5次
    {
        sem_wait(full); // 等待缓冲区为满
        printf("consumer has read data\n");
        printf("the shard_num is %d\n", shard_num); // 读取并打印数据
        sleep(1); // 模拟消费过程的时间消耗
        sem_post(empty); // 通知生产者缓冲区已空
    }
    return NULL;
}
 
int main()
{
    // 动态分配内存给信号量
    full = malloc(sizeof(sem_t));
    empty = malloc(sizeof(sem_t));
 
    // 初始化信号量，empty初始值为1（表示缓冲区初始为空），full初始值为0（表示缓冲区初始不满）
    sem_init(empty, 0, 1);
    sem_init(full, 0, 0);
 
    // 创建生产者和消费者线程
    pthread_t producer_id, consumer_id;
    pthread_create(&producer_id, NULL, producer, NULL);
    pthread_create(&consumer_id, NULL, consumer, NULL);
 
    // 等待生产者和消费者线程完成
    pthread_join(producer_id, NULL);
    pthread_join(consumer_id, NULL);
 
    // 销毁信号量
    sem_destroy(empty);
    sem_destroy(full);
 
    // 程序结束
    return 0;
}