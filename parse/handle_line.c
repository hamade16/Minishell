#include "../minishell.h"
#include <stdio.h>

void	test_execve(char *line)
{
	int		fork_id;
	char	*args1[] = {"-l", NULL};
	char	*args2[] = {"-l", "-a", NULL};
	char	*args3[] = {"-l", "-A", NULL};
	char	*args4[] = {"-la", NULL};
	char	*args5[] = {"-la", "/bin", NULL};
	char	*args6[] = {"", "/bin", NULL};
    char	*env[] = {"PATH=/bin", "USER=me", NULL};

	if (!ft_strcmp(line, "1"))
	{
		printf("here 1\n");
		// new process for command
		fork_id = fork();
		if (fork_id == 0) {
			if (execve("/bin/ls", args1, env) == -1)
			{
				// printf("failed\n");
				perror(NULL);
				// discard new process
				exit(EXIT_FAILURE);
			}
		}
	}
	if (!ft_strcmp(line, "2"))
	{
		printf("here 2\n");
		fork_id = fork();
		if (fork_id == 0) {
			if (execve("/bin/ls", args2, env) == -1)
			{
				// printf("failed\n");
				perror(NULL);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (!ft_strcmp(line, "3"))
	{
		printf("here 3\n");
		fork_id = fork();
		if (fork_id == 0) {
			if (execve("/bin/ls", args3, env) == -1)
			{
				printf("failed\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	if (!ft_strcmp(line, "4"))
	{
		printf("here 4\n");
		fork_id = fork();
		if (fork_id == 0) {
			if (execve("/bin/ls", args4, env) == -1)
			{
				// printf("failed\n");
				perror(NULL);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (!ft_strcmp(line, "5"))
	{
		printf("here 5\n");
		fork_id = fork();
		if (fork_id == 0)
		{
			if (execve("/bin/ls", args5, NULL) == -1)
			{
				// printf("failed\n");
				perror(NULL);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (!ft_strcmp(line, "6"))
	{
		printf("here 5\n");
		fork_id = fork();
		if (fork_id == 0)
		{
			if (execve("/bin/ls", args6, NULL) == -1)
			{
				// printf("failed\n");
				perror(NULL);
				exit(EXIT_FAILURE);
			}
		}
	}

	// wait for child process to finish
	if (fork_id != 0)
		wait(NULL);
}

/*
 * 0	: Quotes are enclosed
 * else	: Quotes are not enclosed
 */
int	check_quotes(char *str)
{
	size_t	i;
	int		quote;

	// check not closed quote
	i = -1;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '"' && quote == 0)
			quote = 2;
		else if (str[i] == '\'' == quote == 1)
			quote = 0;
		else if (str[i] == '"' && quote == 2)
			quote = 0;
	}
	return (quote);
}

int	check_pipes(char *l)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (l[++i])
	{
		if (l[i] == '\'' && quote == 0)
			quote = 1;
		else if (l[i] == '"' && quote == 0)
			quote = 2;
		else if (l[i] == '\'' == quote == 1)
			quote = 0;
		else if (l[i] == '"' && quote == 2)
			quote = 0;

		if (l[i] == '|' && quote == 0) {
			if (l[i + 1] == '|')
				return (0);
		}
	}
	return (1);
}

int	check_redirections(char *s)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		if (s[i] == '\'' && quote == 0)
			quote = 1;
		else if (s[i] == '"' && quote == 0)
			quote = 2;
		else if (s[i] == '\'' == quote == 1)
			quote = 0;
		else if (s[i] == '"' && quote == 2)
			quote = 0;
	// check some errors
	/*
		||
		<>
		><
		<<>
		>><
		<<<
		>>>
		$ [a-zA-Z][?]
	*/
		if (quote == 0)
		{
			if (s[i] == '>')
			{
				if (s[i + 1] == '<')
					return (0);
				if (s[i + 1] == '>')
					if (s[i + 2] == '>')
						return (0);
			}
			else if (s[i] == '<')
			{
				if (s[i + 1] == '>')
					return (0);
				if (s[i + 1] == '<')
					if (s[i + 2] == '<')
						return (0);
			}
			else if (s[i] == '$')
			{
				j = i;
				while (s[j] && s[j] != ' ')
				{
					j++;
				}
				// if (s[i + 1] == '?')
				// else if (ft_isalpha(s[i + 1])
			}
		}
	}
	return (1);
}

// TODO :
	// new list n new cmd in while
t_lst_cmd	handle_line(char *line)
{
	size_t		i;
	size_t		j;
	size_t		quote;
	t_cmd		*cmd;
	t_lst_cmd	*lst_cmd;
	t_lst_cmd	*lst_tmp;
	t_lst_cmd	*head_cmd;

	char	**cmds;

	i = -1;
	j = -1;
	quote = 0;
	if (!check_quotes(line))
	{
		// ||
		if (check_pipes(line))
		{
			if (check_redirections(line))
			{
				cmds = ft_split_wq(line, '|');
				while (cmds[++i])
				{
					;
				}
			}
			else
				printf("minishell: syntax error");
		}
		else
			printf("minishell: syntax error");
	}
	else
		printf("minishell: forbidden error");
}
