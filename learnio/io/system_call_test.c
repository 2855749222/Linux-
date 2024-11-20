#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("text.txt",O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd,buffer,sizeof(buffer)))>0)
    {
        write(STDOUT_FILENO,buffer,bytes_read);
    }
    if(bytes_read == -1)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
    
}