#include "../minishell.h"

void	ex_in_childs(struct imp **imp, char **envp)
{
	int pid;

	pid = fork();

	if (!pid)
	{
		if (g_cmds->is_builtin)
		{
			if (!ft_strcmp(g_cmds->cmd, "echo"))
				impecho();
			if (!ft_strcmp(g_cmds->cmd, "pwd"))
				ft_pwd();
			if(!ft_strcmp(g_cmds->cmd, "env"))
				print_env(imp);
		}
		else
			ft_execve_red(envp);
	}
	wait(&pid);
}