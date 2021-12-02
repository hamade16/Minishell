#include "../minishell.h"

void    ft_exit()
{
	if (g_global->sig_exdeja == 1)
    	printf("exit");
	else
		printf("exit\n");
    exit(0);
}