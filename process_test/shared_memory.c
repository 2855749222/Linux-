#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char * share;
    char shm_name[100] = {0};
    //1,创建一个共享内存对象
    sprintf(shm_name,"/letter%d",getpid());

    //共享内存对象的文件标识符
    int fd;
    fd = shm_open(shm_name, O_CREAT | O_RDWR, 0644);
    if(fd < 0)
    {
        perror("共享内存对象开启失败!\n");
        exit(EXIT_FAILURE);
    }
    //2,设置共享内存大小
    ftruncate(fd,1023);

    //3,内存映射
    share = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    // 注意:不是 share == NULL 映射失败返回的是((void *) -1)
    if(share == MAP_FAILED)
    {
        perror("共享内存对象映射到内存失败!\n");
        exit(EXIT_FAILURE);
    }
    // 映射区建立完毕,关闭读取连接 注意不是删除
    close(fd);

    //4,使用内存映射实现进程间的通讯
    //创建子进程
    pid_t pid = fork();
    if(pid == 0)
    {
        // 子进程写入数据作为回信 
        strcpy(share,"获得好人卡\n");
        printf("新学员%d完成回信!\n", getpid());
    }
    else
    {
        // 等待回信
        sleep(1);
        printf("老学员%d看到新学员%d回信的内容: %s", getpid(),pid,share);
        // 等到子进程运行结束
        wait(NULL);
        //5,释放映映射区
        int ret = munmap(share, 1024);
        if(ret == -1)
        {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
    }

    //删除共享内存对象 注意 参数是地址
    shm_unlink(shm_name);
    return 0;

}