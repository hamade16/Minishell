#include "../minishell.h"

void	ex_in_childs(struct imp **imp, char **envp)
{
	int pid;

	//pid = fork();

	//if (!pid)
	{
		if (g_cmds->is_builtin)
		{
			if (!ft_strcmp(g_cmds->cmd, "echo"))
			{
				pid = fork();
				if (pid == 0)
					impecho();
				wait(&pid);

			}
			if (!ft_strcmp(g_cmds->cmd, "pwd"))
			{
				pid = fork();
				if (pid == 0)
					ft_pwd();
				wait(&pid);
			}
			if(!ft_strcmp(g_cmds->cmd, "env"))
			{
				pid = fork();
				if (pid == 0)
					print_env(imp);
				wait(&pid);
			}
			if (!ft_strcmp(g_cmds->cmd, "export") && (g_cmds->options[1] == NULL))
			{
				pid = fork();
				if (pid == 0)
					print_export(imp);
				wait(&pid);
			}
		}
		else
			ft_execve(envp);
	}
	//wait(&pid);
}