#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	char		*line;
	struct imp	*imp;
	struct imp	*imp_env;

	g_cmds = NULL;
	imp = gere_exp(envp);
	while (1)
	{
		line = readline("minishell% ");

		// if line is not empty
		// add it to history
		if (*line && ft_strlen(ft_strtrim(line, " ")) > 0) {
			add_history(line);
			handle_line(line);
			execute(&imp, envp);
		}

		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		free(line);
	}
	return (0);
}