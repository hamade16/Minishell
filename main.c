#include "minishell.h"

void	handlsignal(int sig)
{

	if (sig == SIGINT)
	{
		printf("\n");
		g_global->sig_exdeja = 1;
		if (g_global->child_ex == 1)
		{
			//printf("\n");
				//close(g_global->close_fd);
				exit(0);
		}
		else
		{
			//printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			//if (!(g_global->lst->options[1] == NULL && !ft_strcmp(g_global->lst->cmd, "cat")))

			if (g_global->her_ex == 1)
			{
				
				g_global->sig_ex = 1;
				//printf("***%d**\n", g_global->her_ex);
				int stdout_copy = dup(1);
				close(1);
				rl_redisplay();
				dup2(stdout_copy, 1);
				g_global->her_ex = 0;
				//printf("hello FILE %d\n", g_global->her_ex);
			}
			else
			{
				rl_redisplay();
			}
		}
		//printf ("***%d***\n", g_global->her_ex);
	}
	else if (sig == SIGQUIT)
	{
		// exit(0);
	}
}

int	main(int ac, char **argv, char **envp)
{
	char		*line;
	struct imp	*imp;

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
	//error = 0;
	while (1)
	{
		line = readline("minishell% ");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		handle_line(line, imp);
		if (line && *line && ft_strlen(ft_strtrim(line, " ")) > 0) {
			add_history(line);
			handle_line(line, imp);
			//print_cmd(g_global->lst);
			execute(&imp, envp);
			free(line);
		}

		if (!line)
		{
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}