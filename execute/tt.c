/*#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
    int fd;
    int child;
    int tmp_fd;

    fd = open("a", O_WRONLY | O_CREAT, 0644);
    //dup2(fd, 1);
    //child = fork();
    if (fd != 1)
    {
        tmp_fd = dup(1);
        dup2(fd, STDOUT_FILENO);
        // close(fd);
    // }
//    execve("/bin/ls", av, NULL);
    // printf("opened the fd = % d\n", fd);
    // dup2(tmp_fd, 1);

}*/