#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell% ");

		// if line is not empty
		// add it to history
		if (*line) {
			add_history(line);
			handle_line(line);
			execute();
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