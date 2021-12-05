#include "../minishell.h"

void	ex_in_childs(struct imp **imp)
{
	int pid;

	{
		if (g_global->lst->is_builtin)
		{
			if (!ft_strcmp(g_global->lst->cmd, "echo"))
			{
				pid = fork();
				if (pid == 0)
				{
					impecho();
					exit(0);
				}
				waitpid(pid, NULL, 0);

			}
			if (!ft_strcmp(g_global->lst->cmd, "pwd"))
			{
				pid = fork();
				if (pid == 0)
				{
					ft_pwd();
					exit(0);
				}
				waitpid(pid, NULL, 0);
			}
			if(!ft_strcmp(g_global->lst->cmd, "env"))
			{
				pid = fork();
				if (pid == 0)
				{
					print_env(imp);
					exit(0);
				}
				waitpid(pid, NULL, 0);
			}
			if (!ft_strcmp(g_global->lst->cmd, "export") && (g_global->lst->options[1] == NULL))
			{
				pid = fork();
				if (pid == 0)
				{
					print_export(imp);
					exit(0);
				}
				waitpid(pid, NULL, 0);
			}
		}
		else
			ft_execve(imp);
	}
	//wait(&pid);
}