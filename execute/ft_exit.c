#include "../minishell.h"

void    ft_exit()
{
	// rl_replace_line("", 0);
	if (g_global->sig_exdeja == 1)
    	printf("exit");
	else
		printf("exit\n");
    exit(0);
}