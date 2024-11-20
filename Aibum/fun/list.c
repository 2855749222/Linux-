#include "../include/list.h"
int show_Undo(int **lcdbuf)
{
    if (lcdbuf == NULL)
    {
        printf("show_Undo: lcdbuf is NULL\n");
        return -1;
    }
    // 1. 打开液晶屏文件
    printf("open lcd\n");
    int lcdFd = open("/dev/fb0", O_RDWR);
    if (lcdFd == -1)
    {
        perror("open lcd error");
        free(lcdbuf);
        return -1;
    }
    // 7. 映射液晶屏的内存
    int *lcd_p = (int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcdFd, 0);
    if (lcd_p == MAP_FAILED)
    {
        perror("mmap error");
        close(lcdFd);
        return -1;
    }
    // 8. 显示图片s
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if (i >= 50 && j < 700)
            {
                lcd_p[i * 800 + j] = lcdbuf[i - 50][j];
            }
        }
    }
    printf("显示成功\n");
    munmap(lcd_p, 800 * 480 * 4);

    close(lcdFd);
    return 1;
}
int **initdata()//初始化数据
{
    int **lcdbuf = (int **)malloc(sizeof(int *) * 430);
    for (int i = 0; i < 430; i++)
    {
        lcdbuf[i] = (int *)malloc(sizeof(int) * 700);
    }
    return lcdbuf;
}

void creat_stack_list()//创建栈
{
    Undo = malloc(sizeof(stack));
    Redo = malloc(sizeof(stack));
    stack *newNode = malloc(sizeof(stack));
    newNode->data = initdata();
    for (int i = 0; i < 430; i++)
    {
        for (int j = 0; j < 700; j++)
        {
            newNode->data[i][j] = BOARD_COLOR;
        }
    }
    newNode->next = NULL;
    Undo->next = newNode;
    Redo->next = NULL;
}
int **get_status(int **board_status, int **new_status)//获取状态
{

    for (int i = 0; i < 430; i++)
    {
        for (int j = 0; j < 700; j++)
        {
            new_status[i][j] = board_status[i][j];
        }
    }
    return new_status;
}
stack *insert__Redo_tlist(stack *head) // 插入Redo
{
    printf("插入Redo成功\n");
    if (Undo->next->next == NULL)
    {
         printf("恢复栈为空\n");
        return head;
    }
    stack *newNode = malloc(sizeof(stack));//创建新节点
    newNode->next = head->next;
    newNode->data = initdata();
    newNode->data = get_status(Undo->next->data, newNode->data);
    head->next = newNode;
    return head;
}
stack *pop_Redo_list(stack *head) // 弹出Redo
{
    printf("pop_Redo\n");
    if (head->next == NULL)
    {
        printf("Redo_empty\n");
        return head;
    }
    stack *temp = head->next; // temp指向第一个节点
    head->next = temp->next;
    show_Undo(temp->data);
    temp->next = Undo->next; // 将temp节点插入到Undo的下一个节点
    Undo->next = temp;
    return head;
}
stack *insertlist(stack *head)//插入栈节点
{
    printf("插入成功\n");
    stack *newNode = malloc(sizeof(stack));
    newNode->next = head->next;
    newNode->data = initdata();
    newNode->data = get_status(head->next->data, newNode->data);
    head->next = newNode;
    return head;
}
stack *poplist(stack *head)//弹出栈节点
{
    printf("pop\n");
    if (head->next->next == NULL) // 必须保留白板
    {
        printf("empty\n");
        return head;
    }
    printf("pop1\n");
    stack *temp = head->next;
    show_Undo(temp->next->data);

    printf("pop2\n");
    if (temp->data != NULL)
    {
        int numRows = 430;
        for (int i = 0; i < numRows; i++)
        {
            free(temp->data[i]);
            temp->data[i] = NULL;
        }
        free(temp->data);
        temp->data = NULL;
    }
    head->next = temp->next;
    free(temp);
    temp = NULL;
    printf("pop3\n");
    return head;
}
stack *delete_list_stack(stack *head) // 删除
{
    printf("delete_Redo\n");
    if (head->next == NULL)
    {
        printf("Redo_empty\n");
        return head;
    }
    // temp指向第一个节点
    while (head->next)
    {
        stack *temp = head->next;
        head->next = temp->next;
        if (temp->data != NULL)
        {
            int numRows = 430;
            for (int i = 0; i < numRows; i++)
            {
                free(temp->data[i]);
                temp->data[i] = NULL;
            }
            free(temp->data);
            temp->data = NULL;
        }
        free(temp); // 释放temp节点
        temp = NULL;
    }
     return head;
}
int ** delete_inmage_data(int**array ,int row,int col) // 删除二维数组
{
    for (int i = 0; i < row; i++)
    {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
    array = NULL;
    return array;
}