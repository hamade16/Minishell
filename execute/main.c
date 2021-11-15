#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    int fd = open("rkiz", O_RDWR | O_CREAT, 0644);

    //printf("Fd: %d %d\n",fd,errno);
    int childs;

    childs = fork();
    if (childs > 0)
    {
        wait(0);
    }
    else
    {
    dup2(fd,1);
    printf("abc\n");

    }
    return (0);
}