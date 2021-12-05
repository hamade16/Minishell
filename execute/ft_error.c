#include "../minishell.h"

void	ft_error(char *str1, char *str2, char *str3)
{
	ft_putstr_fd("minishell:  ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd("\n", 2);
	g_global->error = str3;
}