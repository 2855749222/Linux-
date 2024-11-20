#include "include/Tic_tac_toe.h"
#define ROSE 1
struct msgbuf
{
    long msgtype;
    char msgtext[100];
};
int insert(char **Chessboard, int num, char ch) // 插入棋子
{
    if (num < 4)
    {
        if (Chessboard[0][num - 1] == 'O' || Chessboard[0][num - 1] == 'X')
        {
            showfont("已经有棋子了,请重新输入");
            sleep(1);
            return 0;
        }
        Chessboard[0][num - 1] = ch;
    }
    else if (num < 7 && num > 3)
    {
        if (Chessboard[1][num % 3 != 0 ? num % 3 - 1 : num % 3 + 2] == 'O' || Chessboard[1][num % 3 != 0 ? num % 3 - 1 : num % 3 + 2] == 'X')
        {
            showfont("已经有棋子了,请重新输入");
            sleep(1);
            return 0;
        }
        Chessboard[1][num % 3 != 0 ? num % 3 - 1 : num % 3 + 2] = ch;
    }
    else
    {
        if (Chessboard[2][num % 3 != 0 ? num % 3 - 1 : num % 3 + 2] == 'O' || Chessboard[2][num % 3 != 0 ? num % 3 - 1 : num % 3 + 2] == 'X')
        {
            showfont("已经有棋子了,请重新输入");
            sleep(1);
            return 0;
        }
        Chessboard[2][num % 3 != 0 ? num % 3 - 1 : num % 3 + 2] = ch;
    }
    return 1;
}
void showfont(char *buf)
{
    printf("%s", buf);
    struct LcdDevice *lcd = init_lcd("/dev/fb0");
    // 初始化Lcd
    font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

    // 字体大小的设置
    fontSetSize(f, 35);

    // 创建一个画板（点阵图）
    bitmap *bm = createBitmapWithInit(300, 50, 4, getColor(0, 255, 255, 255)); // 也可使用createBitmap函数，改变画板颜色
                                                                               // getColor(0, 255, 0, 0)  ABGR
                                                                               // bitmap *bm = createBitmap(288, 100, 4);
    // 将字体写到点阵图上
    fontPrint(f, bm, 10, 10, buf, getColor(0, 0, 0, 0), 300);

    // 把字体框输出到LCD屏幕上
    show_font_to_lcd(lcd->mp, 0, 0, bm);
    // 关闭字体，关闭画板
    fontUnload(f);
    destroyBitmap(bm);
}
void Gameover(char *buf)
{
    printf("%s", buf);
    struct LcdDevice *lcd = init_lcd("/dev/fb0");
    // 初始化Lcd
    font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

    // 字体大小的设置
    fontSetSize(f, 50);

    // 创建一个画板（点阵图）
    bitmap *bm = createBitmapWithInit(300, 300, 4, getColor(0, 255, 255, 255)); // 也可使用createBitmap函数，改变画板颜色
                                                                                // getColor(0, 255, 0, 0)  ABGR
                                                                                // bitmap *bm = createBitmap(288, 100, 4);
    // 将字体写到点阵图上
    fontPrint(f, bm, 0, 50, buf, getColor(0, 50, 50, 50), 300);

    // 把字体框输出到LCD屏幕上
    show_font_to_lcd(lcd->mp, 250, 90, bm);
    // 关闭字体，关闭画板
    fontUnload(f);
    destroyBitmap(bm);
}
void palygame(char **Chessboard, int **lcdbuf) // 游戏函数
{
    int play1;
    int play2;
    int i = 0;
    int count = 0;
    int status = 1;
    int **X = load_bmp_as_argb("image/X.bmp");
    int **O = load_bmp_as_argb("image/O.bmp");
    while (i < 9) // 最多输入9个
    {
        count += 2;
        showfont("请play1 下子:");
        play1 = insertmap(lcdbuf, X, Chessboard, 'X');
        while (!play1) // 判读是否有相同的
        {
            showfont("请play1重新 下子:");

            play1 = insertmap(lcdbuf, X, Chessboard, 'X');
        }

        if (same(Chessboard) == 1)
        {
            printf("\n");
            showfont("是 play1赢了!");
            playone++;
            break;
        }
        if (count == 10)
        {
            showfont("平局!");
            printf("\n平局!\n");
            break;
        }
        showfont("请play2 下子:");
        play2 = insertmap(lcdbuf, O, Chessboard, 'O');
        while (!play2)
        {
            showfont("请play2重新 下子:");
            play2 = insertmap(lcdbuf, O, Chessboard, 'O');
        }

        if (same(Chessboard) == 2)
        {
            showfont("是 play2赢了!");
            playtwe++;
            break;
        }
        i++;
    }
    cleararray(Chessboard);
}
int same(char **Chessboard) // 判读是否赢游戏
{
    int sum = 0;
    for (int i = 0; i < 3; i++) // 第一种 横排
    {
        sum = 0;
        for (int j = 0; j < 3; j++)
        {
            sum += Chessboard[i][j];
        }
        if (sum == 264)
        {
            return 1;
        }
        else if (sum == 237)
        {
            return 2;
        }
    }

    for (int i = 0; i < 3; i++) // 第二种 竖排
    {
        sum = 0;
        for (int j = 0; j < 3; j++)
        {
            sum += Chessboard[j][i];
        }
        if (sum == 264)
        {
            return 1;
        }
        else if (sum == 237)
        {
            return 2;
        }
    }
    int X1 = Chessboard[0][0] + Chessboard[1][1] + Chessboard[2][2] + 0;
    int X2 = Chessboard[0][2] + Chessboard[1][1] + Chessboard[2][0] + 0;
    if (X1 == 264 || X2 == 264) // 两种交叉情况
    {
        return 1;
    }
    else if (X1 == 237 || X2 == 237)
    {
        return 2;
    }

    return 0;
}
void cleararray(char **Chessboard) // 清除棋盘
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Chessboard[i][j] = '0';
        }
    }
}

// 映射 棋子
void insertpiece(int index, int indey, int **piece, int **lcdbuf)
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if (i >= indey && i < indey + 100 && j >= index && j < index + 100)
            {
                lcdbuf[i][j] = piece[i - indey][j - index];
            }
        }
    }
}
// 插入棋子
int insertmap(int **lcdbuf, int **piece, char **Chessboard, char C)
{
    int x, y, pox;
    int status = 0;
    touch_wait(&x, &y);
    if (x > 100 && x < 300 && y > 50 && y < 160)
    {
        pox = 1;
        status = insert(Chessboard, pox, C);
        if (status)
            insertpiece(150, 55, piece, lcdbuf);
    }
    else if (x > 300 && x < 500 && y > 50 && y < 160)
    {
        pox = 2;
        status = insert(Chessboard, pox, C);
        if (status)
            insertpiece(350, 55, piece, lcdbuf);
    }
    else if (x > 500 && x < 700 && y > 50 && y < 160)
    {
        pox = 3;
        status = insert(Chessboard, pox, C);
        if (status)
            insertpiece(550, 55, piece, lcdbuf);
    }
    else if (x > 100 && x < 300 && y > 160 && y < 320)
    {
        pox = 4;
        status = insert(Chessboard, pox, C);
        if (status)
            insertpiece(150, 190, piece, lcdbuf);
    }
    else if (x > 300 && x < 500 && y > 160 && y < 320)
    {
        pox = 5;
        status = insert(Chessboard, pox, C);
        if (status)
            insertpiece(350, 190, piece, lcdbuf);
    }
    else if (x > 500 && x < 700 && y > 160 && y < 320)
    {
        pox = 6;
        status = insert(Chessboard, pox, C);
        if (status)
            insertpiece(550, 190, piece, lcdbuf);
    }
    else if (x > 100 && x < 300 && y > 320 && y < 450)
    {
        pox = 7;
        status = insert(Chessboard, pox, C);
        if (status)
            insertpiece(150, 350, piece, lcdbuf);
    }
    else if (x > 300 && x < 500 && y > 320 && y < 450)
    {
        pox = 8;
        status = insert(Chessboard, pox, C);
        if (status)
            insertpiece(350, 350, piece, lcdbuf);
    }
    else if (x > 500 && x < 700 && y > 320 && y < 450)
    {
        pox = 9;
        status = insert(Chessboard, pox, C);
        if (status)
            insertpiece(550, 350, piece, lcdbuf);
    }
    show_mmap(lcdbuf);
    return status;
}

int main(int argc, char const *argv[])
{
    playone = 0;
    playtwe = 0;
   
    if (argc < 2)
    {
        printf("file count < 2\n");
        return 1;
    }
    int **lcdbuf = load_bmp_as_argb("image/jing.bmp");
    show_mmap(lcdbuf);

    char **Chessboard = (char **)malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++)
    {
        Chessboard[i] = (char *)malloc(sizeof(char) * 3);
    }
    // 初始化
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            Chessboard[i][j] = '0';
        }
    }
    // 开始游戏
    palygame(Chessboard, lcdbuf);
    int x, y, pox;
    int status = 1;
    while (status)
    {
        Gameover("       游戏结束                                                                             点击继续");
        touch_wait(&x, &y);
        if (x > 250 && x < 550 && y > 90 && y < 390)
        {
            lcdbuf = load_bmp_as_argb("image/jing.bmp");
            show_mmap(lcdbuf);
            palygame(Chessboard, lcdbuf);
        }
        else
        {
            status = 0;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        free(Chessboard[i]);
        Chessboard[i] = NULL;
    }
    free(Chessboard);
    Chessboard = NULL;

    int msgid = msgget(ftok(".", 3), IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }
    struct msgbuf msg;
    bzero(&msg, sizeof(msg));
    msg.msgtext[0] = '0'+playone;
    msg.msgtext[1] = '0'+playtwe;
    msg.msgtype = ROSE;

    msgsnd(msgid, &msg, strlen(msg.msgtext), 0);
    return 0;
}