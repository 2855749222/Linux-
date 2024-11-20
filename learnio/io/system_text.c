#include <stdio.h>
#include <stdlib.h>
int main()
{
    int result =system("ping -c 10 www.atguigu.com");
    if(result != 0)
    {
        printf("error");
        return 1;
 
    }
    return 0;
}
