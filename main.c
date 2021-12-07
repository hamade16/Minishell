#include "minishell.h"

void	handlsignal(int sig)
{
	int	stdout_copy;

	if (sig == SIGINT)
	{
		printf("\n");
		g_global->sig_exdeja = 1;
		if (g_global->child_ex == 1)
			exit(0);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (g_global->her_ex == 1)
		{
			g_global->sig_ex = 1;
			stdout_copy = dup(1);
			close(1);
			rl_redisplay();
			dup2(stdout_copy, 1);
			g_global->her_ex = 0;
			g_global->error = "130";
		}
		else
		{
			rl_redisplay();
			g_global->error = "1";
		}
	}
}

void	free_global_mini(void)
{
	t_mini_cmd	*mini;

	while (g_global->lst->mini_cmd)
	{
		mini = g_global->lst->mini_cmd;
		free(g_global->lst->mini_cmd->filename);
		g_global->lst->mini_cmd = g_global->lst->mini_cmd->next_mini;
		free(mini);
	}
}

void	free_global(void)
{
	int			i;

	if (g_global->lst)
	{
		if (g_global->lst->cmd)
		{
			free(g_global->lst->cmd);
			g_global->lst->cmd = NULL;
		}
		if (g_global->lst->options)
		{
			i = 0;
			while (g_global->lst->options[i])
			{
				free(g_global->lst->options[i]);
				i++;
			}
		}
		free_global_mini();
		free(g_global->lst);
		g_global->lst = NULL;
	}
}

t_imp	*init_main(int ac, char **av, char **envp)
{
	ac = 0;
	av = NULL;
	g_global = pmalloc(sizeof(t_global));
	g_global->lst = NULL;
	g_global->error = "0";
	g_global->child_ex = 0;
	g_global->her_ex = 0;
	g_global->sig_ex = 0;
	g_global->sig_exdeja = 0;
	signal(SIGINT, handlsignal);
	signal(SIGQUIT, SIG_IGN);
	return (gere_exp(envp));
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	char		*trimmd;
	t_imp		*imp;

	imp = init_main(ac, av, envp);
	while (1)
	{
		line = readline("minishell% ");
		trimmd = ft_strtrim(line, " ");
		if (!line)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (*line && ft_strlen(trimmd) > 0)
		{
			add_history(line);
			handle_line(line, imp);
			execute(&imp);
			free_global();
			free(line);
		}
		free(trimmd);
	}
	return (0);
}