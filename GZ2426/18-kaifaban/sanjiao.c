#include <stdio.h>

int main()
{
    int conut = 9;
    int sum[100];
    int temp[100];
    for (int i = 0; i < conut; i++)
    {
        for (int j = conut; j > i; j--)
        {  
            if (i>5)
            {
                 printf(" \b");
            }
            
            printf(" ");
        }

        for (int j = 0; j <= i; j++)
        {
            if (j == 0 || j == i)
            {
                temp[j] = 1;
                printf(" %d ", temp[j]);
            }
            else
            {
                temp[j]=sum[j-1]+sum[j];
                printf(" %d ", temp[j]);
            }
        }
        for (int j = 0; j <=i; j++)
        {
           sum[j] = temp[j];
        }
        
        printf("\n" );
    }
}