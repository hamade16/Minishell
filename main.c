#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	char		*line;
	struct imp	*imp;

	g_cmds = NULL;
	imp = gere_exp(envp);
	error = 0;
	while (1)
	{
		line = readline("minishell% ");

		if (line && *line && ft_strlen(ft_strtrim(line, " ")) > 0) {
			add_history(line);
			handle_line(line, imp);
			// print_cmd(g_cmds);
			execute(&imp, envp);
			free(line);
		}

		if (!line)
		{
			if (line)
				free(line);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}