#include "../minishell.h"

void    ft_exit()
{
	unsigned char	e;

	if (g_global->sig_exdeja == 1)
    	printf("exit");
	else
		printf("exit\n");
	if (g_global->lst->options[1] == NULL)
	    exit(EXIT_SUCCESS);
	else if (g_global->lst->options[2])
		printf("minishell: too many arguments\n");
	else
	{
		e = ft_atoi(g_global->lst->options[1]);
		exit(e);
	}
}