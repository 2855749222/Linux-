#include "include/main.h"
int **joint_map(int **lcdbuf, int dh, int dw, int **init, int eh, int ew, int index, int indey)
{
    for (int i = 0; i < dh; i++)
    {
        for (int j = 0; j < dw; j++)
        {
            if (i >= indey && i < indey + eh && j >= index && j < index + ew)
            {
                lcdbuf[i][j] = init[i - indey][j - index];
            }
        }
    }
    return lcdbuf; // 返回修改后的 lcdbuf
}
void show_score(char *buf)
{
    // 初始化Lcd
    struct LcdDevice *lcd1 = init_lcd("/dev/fb0");

    // 打开字体
    font *f1 = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

    // 字体大小的设置
    fontSetSize(f1, 15);

    // 创建一个画板（点阵图）
    bitmap *bm = createBitmapWithInit(120, 50, 4, getColor(0, 196, 77, 16));

    fontPrint(f1, bm, 5, 3, buf, getColor(0, 0, 0, 0), 120);
    show_font_to_lcd(lcd1->mp, 560, 0, bm);

    // 关闭字体，关闭画板
    fontUnload(f1);
    destroyBitmap(bm);
}
void main(int argc, char const *argv[])
{
    playonescore = 0;
    playtwoscore = 0;
    int subprocess_status;
    // 分裂登录界面子进程
    // __pid_t pid1 = fork();
    // if (pid1 == -1)
    // {
    //     printf("error fork");
    // }
    // else if (pid1 == 0)
    // {
    //     char *args[] = {"/mnt/share/aibum/login", "../image/jing.bmp", NULL};
    //     int re = execve(args[0], args, NULL);
    //     if (re == -1)
    //     {
    //         printf("no call\n");
    //         return 1;
    //     }
    // }
    // else
    // {
    //     waitpid(pid1, &subprocess_status, 0);
    //     printf("young man status :%d\n", subprocess_status);
    // }
    // tiem_status = 1;
    // pthread_t tid;
    // pthread_create(&tid, NULL, show_time, NULL);

    // 进入主界面
    int **lcdbuf = load_bmp_as_argb("image/desktop.bmp");
    int **minjing = load_bmp_as_argb("image/minjing.bmp");
    int **drawapp = load_bmp_as_argb("image/drawapp.bmp");
    int **pick = load_bmp_as_argb("image/pick_a.bmp");
    lcdbuf = joint_map(lcdbuf, 480, 800, minjing, 100, 100, 700, 0);
    lcdbuf = joint_map(lcdbuf, 480, 800, drawapp, 100, 100, 0, 0);
    lcdbuf = joint_map(lcdbuf, 480, 800, pick, 100, 100, 0, 151);
    show_mmap(lcdbuf);
    int x, y;
    char buf[50] = {0};
    sprintf(buf, "玩家一获得了 %d 次 胜利 \n玩家二获得了 %d 次 胜利 ", playonescore, playtwoscore);
    show_score(buf);
    pthread_t tid;
    tiem_status = 1; // 开启时间线程
    pthread_create(&tid, NULL, show_time, NULL);

    while (1)
    {
        touch_wait(&x, &y);
        if (x > 700 && y < 100)
        {
            int subprocess_status;
            char *name = "old";
            printf("pid :%d\n", getpid());
            tiem_status = 0;      // 关闭时间线程
            __pid_t pid = fork(); // 创建子进程
            if (pid == -1)
            {
                printf("error fork");
            }
            else if (pid == 0)
            {
                char *args[] = {"/mnt/share/aibum/tic_tac_toe", "../image/jing.bmp", NULL};
                int re = execve(args[0], args, NULL);
                if (re == -1)
                {
                    printf("no call\n");
                    return 1;
                }
            }
            else
            {
                waitpid(pid, &subprocess_status, 0);
                // 消息队列
                int msgid = msgget(ftok(".", 3), IPC_CREAT | 0666);
                if (msgid == -1)
                {
                    perror("msgget failed");
                    exit(EXIT_FAILURE);
                }
                struct msgbuf msg;
                bzero(&msg, sizeof(msg));
                msgrcv(msgid, &msg, SIZE, ROSE, 0);
               
                playonescore += msg.msgtext[0] - 48 ;
                playtwoscore += msg.msgtext[1] - 48 ;
                

                tiem_status = 1; // 开启时间线程
                show_mmap(lcdbuf);
                pthread_create(&tid, NULL, show_time, NULL);
                sprintf(buf, "玩家一获得了 %d 次 胜利 \n玩家二获得了 %d 次 胜利 ", playonescore, playtwoscore);
                show_score(buf);
            }
        }
        else if (x < 100 && y < 100)
        {
            int subprocess_status;
            char *name = "old";
            printf("pid :%d\n", getpid());
            tiem_status = 0; // 设置时间线程状态
            __pid_t pid = fork();
            if (pid == -1)
            {
                printf("error fork");
            }
            else if (pid == 0)
            {
                char *args[] = {"/mnt/share/aibum/whiteboard", "../image/jing.bmp", NULL};
                int re = execve(args[0], args, NULL);
                if (re == -1)
                {
                    printf("no call\n");
                    return 1;
                }
            }
            else
            {
                waitpid(pid, &subprocess_status, 0);
                printf("%s: %d whait yang man: %d call\n", name, getpid(), pid);
                printf("young man status :%d\n", subprocess_status);
                tiem_status = 1; // 开启时间线程
                pthread_create(&tid, NULL, show_time, NULL);
                show_mmap(lcdbuf);
                sprintf(buf, "玩家一获得了 %d 次 胜利 \n玩家二获得了 %d 次 胜利 ", playonescore, playtwoscore);
                show_score(buf);
            }
        }
        else if (x < 100 && y > 150 && y < 250)
        {
            // 创建图册子进程
            int subprocess_status;
            char *name = "old";
            printf("pid :%d\n", getpid());
            tiem_status = 0; // 设置时间线程状态
            __pid_t pid = fork();
            if (pid == -1)
            {
                printf("error fork");
            }
            else if (pid == 0)
            {
                char *args[] = {"/mnt/share/aibum/picture", "../image/jing.bmp", NULL};
                int re = execve(args[0], args, NULL);
                if (re == -1)
                {
                    printf("no call\n");
                    return 1;
                }
            }
            else
            {
                waitpid(pid, &subprocess_status, 0);
                printf("%s: %d whait yang man: %d call\n", name, getpid(), pid);
                printf("young man status :%d\n", subprocess_status);
                tiem_status = 1; // 开启时间线程
                pthread_create(&tid, NULL, show_time, NULL);
                show_mmap(lcdbuf);
                sprintf(buf, "玩家一获得了 %d 次 胜利 \n玩家二获得了 %d 次 胜利 ", playonescore, playtwoscore);
                show_score(buf);
            }
        }
    }
}