#include "../include/list.h"
// 初始化锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 初始化条件变量 
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void initSnake(int Snakespeed)
{
    head = malloc(sizeof(Snake));
    head->x = 150;
    head->y = 50;
    head->next = NULL;
    head->dir = RIGHT;
    tail = head;
    Nodenumb = 1;
    speed = Snakespeed;
    SnakeNode_size = 25;
    Snaketail_dir = RIGHT; // 初始化尾巴方向
    Newdir = RIGHT;
    Food_x = 150;
    Food_y = 271;
    score = 0;
}
void addSnakeNode()
{
    printf("addSnakeNode");
    newNode = malloc(sizeof(Snake));
    newNode->dir = tail->dir;

    switch (tail->dir)
    {
    case UP:
        if ((tail->y + SnakeNode_size * 2) > 480)
        {
            if (tail->x - SnakeNode_size < 0)
            {
                newNode->x = tail->x + SnakeNode_size;
                newNode->y = tail->y;
                newNode->dir = LEFT;
                break;
            }
            else
            {
                newNode->x = tail->x - SnakeNode_size;
                newNode->y = tail->y;
                newNode->dir = RIGHT;
                break;
            }
        }
        newNode->x = tail->x;
        newNode->y = tail->y + SnakeNode_size;
        break;
    case DOWN:
        if ((tail->y - SnakeNode_size) < 0)
        {
            if (tail->x - SnakeNode_size < 0)
            {
                newNode->x = tail->x + SnakeNode_size;
                newNode->y = tail->y;
                newNode->dir = LEFT;
                break;
            }
            else
            {
                newNode->x = tail->x - SnakeNode_size;
                newNode->y = tail->y;
                newNode->dir = RIGHT;
                break;
            }
        }
        newNode->x = tail->x;
        newNode->y = tail->y - SnakeNode_size;
        break;
    case LEFT:
        if ((tail->x + SnakeNode_size * 2) > 600)
        {
            if (tail->y - SnakeNode_size < 0)
            {
                newNode->x = tail->x;
                newNode->y = tail->y + SnakeNode_size;
                newNode->dir = UP;
                break;
            }
            else
            {
                newNode->x = tail->x;
                newNode->y = tail->y - SnakeNode_size;
                newNode->dir = DOWN;
                break;
            }
        }
        newNode->x = tail->x + SnakeNode_size;
        newNode->y = tail->y;
        break;
    case RIGHT:
        if (tail->x - SnakeNode_size < 0)
        {
            if (tail->y - SnakeNode_size < 0)
            {
                newNode->x = tail->x;
                newNode->y = tail->y + SnakeNode_size;
                newNode->dir = UP;
                break;
            }
            else
            {
                newNode->x = tail->x;
                newNode->y = tail->y - SnakeNode_size;
                newNode->dir = DOWN;
                break;
            }
        }
        newNode->x = tail->x - SnakeNode_size;
        newNode->y = tail->y;
        break;
    }

    newNode->next = NULL;
    tail->next = newNode;
    tail = newNode;
    // 蛇节点个个数加一
    Nodenumb++;
    // printf("%d111111111111111\n", newNode->x);
     printf("addSnakeNode_finsh\n");
}
void clearbrg(int x, int y, int heigth, int width)
{
    int lcdFd = open("/dev/fb0", O_RDWR);
    if (lcdFd == -1)
    {
        perror("open lcd error");

        return;
    }
    int(*lcd_p)[800] = (int(*)[800])mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcdFd, 0);
    for (int i = y; i < heigth; i++)
    {
        for (int j = x; j < width + 1; j++)
        {
            lcd_p[i][j] = lcdbuf[i][j];
        }
    }

    munmap(lcd_p, 800 * 480 * 4);
    close(lcdFd);
}
// 画蛇
void drowSnake()
{

    temp = head;
    if (head->y < 0)
    {
        return;
    }
    int lcdFd = open("/dev/fb0", O_RDWR);
    if (lcdFd == -1)
    {
        perror("open lcd error");

        return;
    }
    int(*lcd_p)[800] = (int(*)[800])mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcdFd, 0);

    while (temp)
    {
        for (int i = temp->y, y = 0; i < temp->y + SnakeNode_size; i++, y++)
        {
            for (int j = temp->x, x = 0; j < temp->x + SnakeNode_size; j++, x++)
            {
                lcd_p[i][j] = Snake_body[y][x];
            }
        }
        tailx = temp->x - 1;
        taily = temp->y;
        temp = temp->next;
    }

    switch (Snaketail_dir)
    {
    case UP:
        if (tail->y + SnakeNode_size * 2 <= 480)
        {
            clearbrg(tailx, taily + SnakeNode_size, taily + SnakeNode_size + SnakeNode_size, tailx + SnakeNode_size);
        }

        break;
    case DOWN:
        if (!(tail->y < 25))
        {
            clearbrg(tailx, taily - SnakeNode_size, taily, tailx + SnakeNode_size);
        }
        break;
    case LEFT:
        if (tail->x + SnakeNode_size < 600)
        {
            clearbrg(tailx + SnakeNode_size, taily, taily + SnakeNode_size, tailx + SnakeNode_size + SnakeNode_size);
        }
        break;
    case RIGHT:
        if (!(tail->x < 26))
        {
            clearbrg(tailx - SnakeNode_size, taily, taily + SnakeNode_size, tailx);
        }
        break;
    }

    // else if (temp->next == NULL && j == temp->x + SnakeNode_size && i == temp->y + SnakeNode_size) // 将上一次移动的蛇尾清除掉
    // {
    // }

    Snaketail_dir = tail->dir;
    munmap(lcd_p, 800 * 480 * 4);
    close(lcdFd);
}
void moveSnake(Snake *Node, int dir)
{
    switch (dir)
    {
    case UP:
        Node->y -= speed;
        break;
    case DOWN:
        Node->y += speed;
        break;
    case LEFT:
        Node->x -= speed;
        break;
    case RIGHT:
        Node->x += speed;
        break;
    }
}
void drowfood(int color)
{  
    printf("drowfood\n");
    int lcdFd = open("/dev/fb0", O_RDWR);
    if (lcdFd == -1)
    { 
        perror("open lcd error");

        return; 
    }
    int(*lcd_p)[800] = (int(*)[800])mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcdFd, 0);
    if (color == WHITE)
    {
        for (int i = Food_y; i < Food_y + SnakeNode_size; i++)
        {
            for (int j = Food_x; j < Food_x + SnakeNode_size; j++)
            {
                lcd_p[i][j] = lcdbuf[i][j];
            }
        }
    }
    else
    {
        for (int i = Food_y, y = 0; i < Food_y + SnakeNode_size; i++, y++)
        {
            for (int j = Food_x, x = 0; j < Food_x + SnakeNode_size; j++, x++)
            {
                lcd_p[i][j] = Foot_dr[y][x];
            }
        }
    }

    munmap(lcd_p, 800 * 480 * 4);
    close(lcdFd);
    printf("drowfood_finish\n");
}
void Eatfoot()
{
    printf("eatfoot\n");
    switch (head->dir)
    {
    case UP:
        if ((head->x > Food_x && head->x < Food_x + SnakeNode_size &&
             head->y < Food_y + SnakeNode_size && head->y > Food_y) ||
            (head->x + SnakeNode_size > Food_x && head->x + SnakeNode_size <= Food_x + SnakeNode_size &&
             head->y < Food_y + SnakeNode_size && head->y > Food_y) ||
            (head->x == Food_x && head->y < Food_y + SnakeNode_size && head->y >= Food_y))
        {
            drowfood(WHITE);
            addSnakeNode();
            score++;
            // 唤醒线程
            pthread_cond_signal(&cond);
        }
        break;
    case DOWN:
        if ((head->x > Food_x && head->x < Food_x + SnakeNode_size &&
             head->y + SnakeNode_size < Food_y + SnakeNode_size && head->y + SnakeNode_size > Food_y) ||
            (head->x + SnakeNode_size > Food_x && head->x + SnakeNode_size < Food_x + SnakeNode_size &&
             head->y + SnakeNode_size < Food_y + SnakeNode_size && head->y + SnakeNode_size > Food_y) ||
            (head->x == Food_x && head->y + SnakeNode_size > Food_y && head->y + SnakeNode_size < Food_y + SnakeNode_size))
        {
            drowfood(WHITE);
            addSnakeNode();
            score++;
            // 唤醒
            pthread_cond_signal(&cond);
        }
        break;
    case LEFT:
        if ((head->x > Food_x && head->x < Food_x + SnakeNode_size &&
             head->y < Food_y + SnakeNode_size && head->y > Food_y) ||
            (head->x > Food_x && head->x < Food_x + SnakeNode_size &&
             head->y + SnakeNode_size < Food_y + SnakeNode_size && head->y + SnakeNode_size > Food_y) ||
            (head->y == Food_y && head->x > Food_x && head->x <= Food_x + SnakeNode_size))
        {
            drowfood(WHITE);
            score++;
            addSnakeNode();
            // 唤醒
            pthread_cond_signal(&cond);
        }
        break;
    case RIGHT:
        if ((head->x + SnakeNode_size > Food_x && head->x + SnakeNode_size < Food_x + SnakeNode_size &&
             head->y < Food_y + SnakeNode_size && head->y > Food_y) ||
            (head->x + SnakeNode_size > Food_x && head->x + SnakeNode_size < Food_x + SnakeNode_size &&
             head->y + SnakeNode_size < Food_y + SnakeNode_size && head->y + SnakeNode_size > Food_y) ||
            (head->y == Food_y && head->x + SnakeNode_size > Food_x && head->x + SnakeNode_size <= Food_x + SnakeNode_size))
        {
            drowfood(WHITE);
            addSnakeNode();
            score++;
            // 唤醒
            pthread_cond_signal(&cond);
        }
        break;
    }
}
void *gameplay(void *arg)
{
    nn = 1;
    int x = 0;
    while (nn)
    {

        temp = head;
        int dir = temp->dir;
        if (x % 25 == 0)
        {
            head->dir = Newdir;
        }
        while (temp)
        {

            moveSnake(temp, temp->dir);
            if (x % 25 == 0 && temp != head)
            {
                int tem = dir;
                dir = temp->dir;
                temp->dir = tem;
            }
            temp = temp->next;
        }

        if (x % 25 == 0)
        {
            Eatfoot();
            game_over();
        }
        drowSnake();
        x++;
        usleep(5000);
    }
    return NULL;
}
void game_over()
{
    if (head->x + 25 > 600 || head->y + 25 > 475 || head->x < 0 || head->y < 0)
    {
        printf("游戏结束!\n");
        nn = 0;
    }
    temp = head->next->next->next;
    while (temp)
    {
        if (abs(head->x - temp->x) < SnakeNode_size - 5 && abs(head->y - temp->y) < SnakeNode_size - 5)
        {
            printf("在蛇上\n");
            nn = 0;
            break;
        }
        temp = temp->next;
    }
}
void *create_foot(void *arg)
{
    // 获取互斥锁 拿不到等
    pthread_mutex_lock(&mutex);
    while (1)
    {
        // 暂停线程 等待唤醒
        printf("暂停暂停暂停暂停暂停暂停暂停\n");
        pthread_cond_wait(&cond, &mutex);
        printf("醒了醒了\n");
        // 获取食物位置
        generateFoodPosition();
        printf("获取食物位置\n");
        drowfood(YELLOW);

        show_score(score);
    }
    // 释放锁
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void generateFoodPosition()
{
    printf("generateFoodPosition\n");
    srand((unsigned)time(NULL)); // 设置随机数种子
    int randomNumber_x;
    int randomNumber_y;
    int onSnake;
    do
    {
        randomNumber_x = 0 + rand() % (600 - SnakeNode_size + 1);
        randomNumber_y = 0 + rand() % (480 - SnakeNode_size + 1);

        onSnake = 0;
        temp = head;
        while (temp)
        {
            if (abs(randomNumber_x - temp->x) < SnakeNode_size && abs(randomNumber_y - temp->y) < SnakeNode_size)
            {
                printf("在蛇上\n");
                onSnake = 1;
                break;
            }
            temp = temp->next;
        }
    } while (onSnake);
    printf("nih\n");
    printf("rand_y : %d\n", randomNumber_y);
    printf("rand_x : %d\n", randomNumber_x);
   

    Food_x = randomNumber_x;
    Food_y = randomNumber_y;
    printf("generateFoodPosition_finish\n");
}
