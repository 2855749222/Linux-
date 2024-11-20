#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define ROSE 1
#define SIZE 100

struct msgbuf
{
    long msgtype;
    char msgtext[SIZE];
};

int main(int argc, char **argv)
{
    //key_t ftok(const char *pathname, int id);
    // pathname 参数是一个已存在的文件路径。
    // id 参数是一个整数，通常是一个字符（通过强制类型转换），用于与文件路径结合生成键值。
    // 返回值是一个 key_t 类型的键值，用于后续的 IPC 操作。如果 ftok 失败，则返回 (key_t)-1。
    int msgid = msgget(ftok(".", 3), IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct msgbuf msg;
  
    while (1)
    {
        bzero(&msg,sizeof(msg));
        fgets(msg.msgtext,SIZE,stdin);
        msg.msgtype = ROSE;

        msgsnd(msgid,&msg,strlen(msg.msgtext),0);
        //int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
        //msgqid：MSG对象的ID，由msgget()获取。
        // msgp：一个指向等待被发送的消息的指针，由于MSG中的消息最大的特点是必须有一个整数标识，用以区分MSG中的不同的消息，因此MSG的消息会使用一个特别的结构体来表达，具体如下所示：
        // struct msgbuf
        // {
        //     // 消息类型（固定）
        //     long mtype;
        //     // 消息正文（可变）
        //     // ...
        // };
        // 因此一般而言，msgp就是一个指向上述结构体的指针。
        // msgsz：消息正文的长度（单位字节），注意不含类型长度。
        // msgflg：发送选项，一般有：
        // 0：默认发送模式，在MSG缓冲区已满的情形下阻塞，直到缓冲区变为可用状态。
        // IPC_NOWAIT：非阻塞发送模式，在MSG缓冲区已满的情形下直接退出函数并设置错误码为EAGAIN.
    }

    return 0;
    
}