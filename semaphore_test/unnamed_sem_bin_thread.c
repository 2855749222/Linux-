#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

int shard_num = 0;
sem_t unnamed_sem;//声明无名信号量

void *plusOne(void *argv) {
    sem_wait(&unnamed_sem); //信号量减一 ，为零则堵塞 //本质等同于读写锁
    int tmp = shard_num + 1;
    shard_num = tmp;
    sem_post(&unnamed_sem); //信号量加一 ，唤醒因为信号量堵塞的线程
}

int main() {
    sem_init(&unnamed_sem,0,1);//初始化无名信号量 0 表示为线程 ，1 表示信号量的初始值
    pthread_t tid[10000]; 
    for (int i = 0; i < 10000; i++) {
        pthread_create(tid + i, NULL, plusOne, NULL);
    }

    for (int i = 0; i < 10000; i++) {
        pthread_join(tid[i], NULL);
            
    }
    
    printf("shard_num is %d\n", shard_num);
    sem_destroy(&unnamed_sem); //回收
    return 0;
}