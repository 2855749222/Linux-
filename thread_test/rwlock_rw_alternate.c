#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//4.3.3.3写操作不加锁测试
pthread_rwlock_t rwlock;
int shared_data = 0;

void *lock_reader(void *argv)
{
    pthread_rwlock_rdlock(&rwlock);
    printf("this is %s, value is %d\n", (char *)argv, shared_data);
    pthread_rwlock_unlock(&rwlock);
}

void *lock_writer(void *argv)
{
    //获取声明的 写锁
    pthread_rwlock_wrlock(&rwlock);
    int tmp = shared_data + 1;
    shared_data = tmp;
    printf("this is %s, shared_data值为 %d\n", (char *)argv,shared_data);
    pthread_rwlock_unlock(&rwlock);
}

int main()
{
    //初始化
    pthread_rwlock_init(&rwlock, NULL);
    pthread_t writer1, writer2, reader1, reader2, reader3, reader4, reader5, reader6;
    //写
    pthread_create(&writer1, NULL, lock_writer, "writer1");
    //读
    pthread_create(&reader1, NULL, lock_reader, "reader1");
    pthread_create(&reader2, NULL, lock_reader, "reader2");
    pthread_create(&reader3, NULL, lock_reader, "reader3");
    //写
    pthread_create(&writer2, NULL, lock_writer, "writer2");
    //读
    pthread_create(&reader4, NULL, lock_reader, "reader4");
    pthread_create(&reader5, NULL, lock_reader, "reader5");
    pthread_create(&reader6, NULL, lock_reader, "reader6");

    pthread_join(writer1, NULL);
    pthread_join(writer2, NULL);
    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);
    pthread_join(reader3, NULL);
    pthread_join(reader4, NULL);
    pthread_join(reader5, NULL);
    pthread_join(reader6, NULL);
    //销毁
    pthread_rwlock_destroy(&rwlock);
}