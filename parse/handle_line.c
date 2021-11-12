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
		// ||, <>, ><, <<>, >><, <<<, >>>
		// $ [a-zA-Z][?]

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
				if (s[i + 1] != '?' || ft_isalpha(s[i + 1]))
					return (0);
			}
		}
	}
	return (1);
}

int		check_empty_pipes(char **cmds)
{
	size_t	i;
	size_t	j;
	int		flag;

	i = -1;
	while (cmds[++i])
	{
		j = -1;
		flag = 0;
		while (cmds[i][++j])
		{
			if (ft_isalnum(cmds[i][j]))
				flag = 1;
		}
		if (!flag)
			return (0);
	}
	return (1);
}

/*
 * redirection at the end
 */
int		check_in_redirections(char **cmds)
{
	size_t	i;
	size_t	j;
	char	*trimmd;
	size_t	len;

	i = -1;
	while (cmds[++i])
	{
		j = 0;
		trimmd = ft_strtrim(cmds[i], " ");
		len = ft_strlen(cmds[i]);

		if (trimmd[len - 1] == '<' || trimmd[len - 1] == '>')
			return (0);
	}
	return (1);
}

// char	*ft_fill_cmdname(char *s)
// {
// 	size_t	i;
// 	char	*trimmd;

// 	i = 0;
// 	trimmd = ft_strtrim(s, " ");
// 	// 
// 	return (trimmd);
// }

void	ft_append(char ***opt, char *newopt)
{
	size_t	i;
	size_t	len;
	char	**tmp;

	if (*opt == NULL)
	{
		*opt = malloc(sizeof(char *) * 2);
		(*opt)[0] = newopt;
		(*opt)[1] = NULL;
	}
	else
	{
		len = 0;
		while ((*opt)[len])
		{
			len++;
		}

		tmp = *opt;
		*opt = malloc(sizeof(char *) * (len + 1 + 1));
		i = 0;
		while (i < len)
		{
			(*opt)[i] = tmp[i];
			i++;
		}
		(*opt)[i] = newopt;
		(*opt)[i + 1] = NULL;
	}
}

void	ft_fill_it(t_cmd **head, char *line)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;

	tmp = malloc(sizeof(t_cmd));

	tmp->text = ft_strdup(line);
	tmp->options = NULL;

	char **opts = ft_split_wq(line, ' ');
	while (opts[i])
	{
		if (i == 0) {
			tmp->cmd = opts[i];
			ft_append(&tmp->options, NULL);
		}
		else
			ft_append(&tmp->options, opts[i]);
		i++;
	}
	tmp->next_cmd = NULL;

	if (*head == NULL)
		*head = tmp;
	else
	{
		cmd = *head;
		while (cmd->next_cmd)
		{
			cmd = cmd->next_cmd;
		}
		cmd->next_cmd = tmp;
	}
}

// TODO :
	// new list n new cmd in while
void	handle_line(char *line)
{
	size_t		i;
	size_t		j;
	t_cmd		*cmd;
	char		**cmds;

	g_cmds = NULL;
	cmd = NULL;
	i = -1;
	j = -1;
	if (!check_quotes(line))
	{
		// ||
		if (check_pipes(line))
		{
			if (check_redirections(line))
			{
				cmds = ft_split_wq(line, '|');

				// check empty splits
				if (check_empty_pipes(cmds))
				{
					// check wrong redirections
					if (check_in_redirections(cmds))
					{
						while (cmds[++i])
						{
							// get data and fill head
							ft_fill_it(&g_cmds, cmds[i]);
						}
					}
				}
				else
					printf("minishell: syntax error\n");
			}
			else
				printf("minishell: syntax error\n");
		}
		else
			printf("minishell: syntax error\n");
	}
	else
		printf("minishell: forbidden error\n");
}
