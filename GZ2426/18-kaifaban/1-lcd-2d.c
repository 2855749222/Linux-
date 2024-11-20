#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    int lcd_fd = open("/dev/fb0",O_WRONLY);

    if(lcd_fd == -1)
    {
        perror("open errar");
        return -1;
    }
    int arr[480*800] = {0};
    int red =  0x00ff0000;
    int greet = 0x0000ff00;
    int blue =  0x000000ff;
    int *color = &red;
    int index = 1;
    while (1)
    {
        if (index == 2)
        {
             color = &greet;
        }
        else if(index == 3)
        {
             color = &blue;
        }
        else
        {
            color = &red;
        }
        lseek(lcd_fd,0,SEEK_SET);
        for (int i = 0; i < 480*800; i++)
        {
            arr[i] = *color;
        }
        if(index == 3){index = 0;}
        index++;
        write(lcd_fd,arr,480*800*4);
        sleep(3);
    }
    
   
    close(lcd_fd);
    return 0;
    


}