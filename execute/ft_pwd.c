#include "../minishell.h"

void    ft_pwd()
{
    char buff[1000];

    printf("%s\n", getcwd(buff, 100));
}