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
				{
					impecho();
					exit(0);
				}
				waitpid(pid, NULL, 0);

			}
			if (!ft_strcmp(g_cmds->cmd, "pwd"))
			{
				pid = fork();
				if (pid == 0)
				{
					ft_pwd();
					exit(0);
				}
				waitpid(pid, NULL, 0);
			}
			if(!ft_strcmp(g_cmds->cmd, "env"))
			{
				pid = fork();
				if (pid == 0)
				{
					print_env(imp);
					exit(0);
				}
				waitpid(pid, NULL, 0);
			}
			if (!ft_strcmp(g_cmds->cmd, "export") && (g_cmds->options[1] == NULL))
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
			ft_execve(envp);
	}
	//wait(&pid);
}