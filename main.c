#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	char		*line;
	struct imp	*imp;

	g_global = malloc(sizeof(t_global));
	g_global->lst = NULL;
	g_global->error = "0";
	imp = gere_exp(envp);
	//error = 0;
	while (1)
	{
		line = readline("minishell% ");

		if (line && *line && ft_strlen(ft_strtrim(line, " ")) > 0) {
			add_history(line);
			handle_line(line, imp);
			// print_cmd(g_global->lst);
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