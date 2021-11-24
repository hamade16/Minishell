/*#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int fd;

	fd = open("/tmp/heredocfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		char *line;
   		line = readline(">");
		if (ft_strcmp(line, "ha"))
		{
			ft_putendl_fd(line, fd);
		}
		else
			break;
	}
	close(fd);
}*/

