#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
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
    int msgid = msgget(ftok(".", 3), IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct msgbuf msg;

    while (1)
    {
        bzero(&msg, sizeof(msg));
        msgrcv(msgid, &msg, SIZE, ROSE, 0);
        // ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
        //  msgqid：MSG对象的ID，由msgget()获取。
        //  msgp：存放消息的内存入口。
        //  msgsz：存放消息的内存大小。
        //  msgtyp：欲接收消息的类型：
        //  0：不区分类型，直接读取MSG中的第一个消息。
        //  大于0：读取类型为指定msgtyp的第一个消息（若msgflg被配置了MSG_EXCEPT则读取除了类型为msgtyp的第一个消息）。
        //  小于0：读取类型小于等于msgtyp绝对值的第一个具有最小类型的消息。例如当MSG对象中有类型为3、1、5类型消息若干条，当msgtyp为-3时，类型为1的第一个消息将被读取。
        //  msgflg：接收选项：
        //  0：默认接收模式，在MSG中无指定类型消息时阻塞。
        //  IPC_NOWAIT：非阻塞接收模式，在MSG中无指定类型消息时直接退出函数并设置错误码为ENOMSG.
        //  MSG_EXCEPT：读取除msgtyp之外的第一个消息。
        //  MSG_NOERROR：如果待读取的消息尺寸比msgsz大，直接切割消息并返回msgsz部分，读不下的部分直接丢弃。若没有设置该项，则函数将出错返回并设置错误码为E2BIG。
        printf("from receive : %s", msg.msgtext);
    }

    return 0;
}