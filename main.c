#include "minishell.h"

void	handlsignal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_global->sig_exdeja = 1;
		if (g_global->child_ex == 1)
		{
			exit(0);
		}
		else
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			if (g_global->her_ex == 1)
			{
				g_global->sig_ex = 1;
				int stdout_copy = dup(1);
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
	else if (sig == SIGQUIT)
	{
		if (g_global->child_ex == 1)
		{
			//g_global->sig_ex = 1;
				//close(g_global->close_fd);
			exit(0);
		}
		else
		{
			if (g_global->her_ex == 1)
			{
				printf("Quit: 3\n");
				g_global->error = "131";

			}
			//printf("%s\n", g_global->lst->cmd);
			//printf("***hamade***\n");
			//printf("Quit: 3\n");
			//g_global->sig_ex = 1;
			signal(SIGQUIT, SIG_IGN);
			
		}
	}
}

int	main(int ac, char **argv, char **envp)
{
	char		*line;
	struct imp	*imp;
	// int i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }

	g_global = malloc(sizeof(t_global));
	g_global->lst = NULL;
	g_global->error = "0";
	imp = gere_exp(envp);
	g_global->child_ex = 0;
	g_global->her_ex = 0;
	g_global->sig_ex = 0;
	g_global->sig_exdeja = 0;
	signal(SIGINT, handlsignal);
	signal(SIGQUIT, handlsignal);
	while (1)
	{
		line = readline("minishell% ");
		if (!line)
		{
			printf("exit");
			exit(EXIT_SUCCESS);
		}
		else if (*line && ft_strlen(ft_strtrim(line, " ")) > 0)
		{
			add_history(line);
			handle_line(line, imp);
			// print_cmd(g_global->lst);
			execute(&imp, envp);
			free(line);
		}
	}
	return (0);
}