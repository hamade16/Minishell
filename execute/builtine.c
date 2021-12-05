#include "../minishell.h"

void	is_builtin(struct imp **imp)
{
	int i;


	if (!ft_strcmp(g_global->lst->cmd, "export"))
	{
		if (g_global->lst->options[1] != NULL)
			imp = manages_options(imp);
		else
			print_export(imp);
	}
	if (!ft_strcmp(g_global->lst->cmd, "echo"))
		impecho();
	if (!ft_strcmp(g_global->lst->cmd, "unset"))
		imp = ft_unset(imp);
	if (!ft_strcmp(g_global->lst->cmd, "cd"))
		i = ft_cd(imp);
	if (!ft_strcmp(g_global->lst->cmd, "pwd"))
		ft_pwd();
	if(!ft_strcmp(g_global->lst->cmd, "exit"))
		ft_exit();
	if(!ft_strcmp(g_global->lst->cmd, "env"))
		print_env(imp);
}