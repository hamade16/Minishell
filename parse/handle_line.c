#include "../execute/minishell_execute.h"
#include "../minishell.h"
#include <stdio.h>

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
	return (!quote);
}

int	check_quotes_ind(char *str, size_t len)
{
	size_t	i;
	int		quote;

	// check not closed quote
	i = -1;
	quote = 0;
	while (str[++i] && i < len + 1)
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

// TODO
	// unquote then check last pipe
/*
 * double pipes
 * pipe is the last thing (not quoted)
 */
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
	size_t len = ft_strlen(ft_strtrim(l, " "));
	if (ft_strtrim(l, " ")[len - 1] == '|')
		return (0);
	return (1);
}

/*
 * check some errors
 * ||, <>, ><, <<>, >><, <<<, >>>
 * $ [a-zA-Z][?]
 * on error 0
 * on success 1
 */
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
		}
	}
	return (1);
}

/*
 * on error 0
 * on success 1
 */
int		check_vars(char *s)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && quote == 0)
			quote = 1;
		else if (s[i] == '"' && quote == 0)
			quote = 2;
		else if (s[i] == '\'' == quote == 1)
			quote = 0;
		else if (s[i] == '"' && quote == 2)
			quote = 0;
		if (s[i] == '$' && quote != 1)
		{
			if (s[i + 1] != '?' && s[i + 1] != '_' && !ft_isalpha(s[i + 1]))
				return (0);
		}
		i++;
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
			if (cmds[i][j] != ' ')
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
		len = ft_strlen(trimmd);
		if (trimmd[len - 1] == '<' || trimmd[len - 1] == '>')
			return (0);
	}
	return (1);
}

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
	size_t		i;
	size_t		j;
	size_t		k;
	char		**parts;
	t_cmd		*cmd;
	t_cmd		*tmp;
	t_mini_cmd	*mini;
	char		*filename;
	int			redirection;

	i = 0;

	tmp = malloc(sizeof(t_cmd));

	tmp->text = ft_strdup(line);
	tmp->cmd = NULL;
	tmp->options = NULL;
	tmp->mini_cmd = NULL;

	mini = NULL;
	filename = NULL;
	redirection = 0;

	parts = ft_split_wq(line, ' ', 0, 0);
	while (parts[i])
	{
		j = 0;
		while (parts[i][j])
		{
			// if redirection
			if (parts[i][j] == '>')
			{
				// get type
				if (parts[i][j + 1] == '>')
				{
					redirection = 3;
					j++;
				}
				else
				{
					redirection = 1;
				}
				j++;
			}
			else if (parts[i][j] == '<')
			{
				// get type
				if (parts[i][j + 1] == '<')
				{
					redirection = 4;
					j++;
				}
				else
				{
					redirection = 2;
				}
				j++;
			}
			else if (parts[i][j] == '-')
			{
				k = j;
				j++;
				while (parts[i][j] && parts[i][j] != '<' && parts[i][j] != '>')
					j++;
				if (tmp->cmd == NULL)
				{
					tmp->cmd = ft_substr(parts[i], k, j - k);
					ft_append(&tmp->options, ft_substr(parts[i], k, j - k));
					if (!ft_strcmp(tmp->cmd, "export") || !ft_strcmp(tmp->cmd, "echo") ||
						!ft_strcmp(tmp->cmd, "unset") || !ft_strcmp(tmp->cmd, "cd") ||
						!ft_strcmp(tmp->cmd, "pwd") || !ft_strcmp(tmp->cmd, "pwd") ||
						!ft_strcmp(tmp->cmd, "env") || !ft_strcmp(tmp->cmd, "exit"))
						tmp->is_builtin = 1;
					else
						tmp->is_builtin = 0;
				}
				else
					ft_append(&tmp->options, ft_substr(parts[i], k, j - k));
			}
			else
			{
				k = j;
				// TODO
				if (parts[i][j] == '\'' || parts[i][j] == '"')
					j++;
				while (parts[i][j] && ((parts[i][j] != '<' && parts[i][j] != '>') || check_quotes_ind(parts[i], j)))
					j++;
				if (tmp->cmd == NULL)
				{
					tmp->cmd = ft_substr(parts[i], k, j - k);
					ft_append(&tmp->options, ft_substr(parts[i], k, j - k));
					if (!ft_strcmp(tmp->cmd, "export") || !ft_strcmp(tmp->cmd, "echo") ||
						!ft_strcmp(tmp->cmd, "unset") || !ft_strcmp(tmp->cmd, "cd") ||
						!ft_strcmp(tmp->cmd, "pwd") || !ft_strcmp(tmp->cmd, "pwd") ||
						!ft_strcmp(tmp->cmd, "env") || !ft_strcmp(tmp->cmd, "exit"))
						tmp->is_builtin = 1;
					else
						tmp->is_builtin = 0;
				}
				else if (redirection)
				{
					filename = ft_substr(parts[i], k, j - k);
					ft_mini_addback(&tmp->mini_cmd, filename, redirection);
					free(filename);
					filename = NULL;
					redirection = 0;
				}
				else
				{
					ft_append(&tmp->options, ft_substr(parts[i], k, j - k));
				}
				// j++;
			}
		}
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

char	*expand_it(char *s, struct imp *env)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	var_size;
	int		quote;
	char	*res;
	char	*var_key;
	struct imp *head;

	i = 0;
	size = 0;
	var_size = 0;
	quote = 0;
	var_key = NULL;
	res = NULL;

	while (s[i])
	{
		if (s[i] == '\'' && quote == 0)
			quote = 1;
		else if (s[i] == '"' && quote == 0)
			quote = 2;
		else if (s[i] == '\'' == quote == 1)
			quote = 0;
		else if (s[i] == '"' && quote == 2)
			quote = 0;
		
		if (s[i] == '$' && quote != 1)
		{
			i++;
			var_size = 1;
			if (ft_isalpha(s[i]) || s[i] == '_' || s[i] == '?')
			{
				i++;
				var_size++;
				while (ft_isalnum(s[i]))
				{
					var_size++;
					i++;
				}
			}

			var_key = ft_substr(s, i - var_size + 1, var_size - 1);
			head = env;
			while (head)
			{
				if (ft_strcmp(var_key, head->key) == 0)
				{
					size += ft_strlen(head->value);
				}
				head = head->next;
			}
		}

		if (s[i])
		{
			size++;
			i++;
		}
	}

	i = 0;
	j = 0;
	var_size = 0;
	quote = 0;
	res = malloc(sizeof(char) * size + 1);

	while (s[i])
	{
		if (s[i] == '\'' && quote == 0)
			quote = 1;
		else if (s[i] == '"' && quote == 0)
			quote = 2;
		else if (s[i] == '\'' == quote == 1)
			quote = 0;
		else if (s[i] == '"' && quote == 2)
			quote = 0;
		
		if (s[i] == '$' && quote != 1)
		{
			i++;
			var_size = 1;
			if (ft_isalpha(s[i]) || s[i] == '_' || s[i] == '?')
			{
				i++;
				var_size++;
				while (ft_isalnum(s[i]))
				{
					var_size++;
					i++;
				}
			}

			var_key = ft_substr(s, i - var_size + 1, var_size - 1);
			head = env;
			while (head)
			{
				if (ft_strcmp(var_key, head->key) == 0)
				{
					ft_strlcpy(res+j, head->value, ft_strlen(head->value) + 1);
					j += ft_strlen(head->value);
				}
				head = head->next;
			}
		}
		else
		{
			res[j] = s[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	return (res);
}

// TODO
	// fix checks
		// check unclosed quotes
	// remove quotes
void	handle_line(char *line, struct imp *env)
{
	size_t		i;
	t_cmd		*cmd;
	char		**cmds;
	char		*tmp;

	g_cmds = NULL;
	cmd = NULL;
	i = -1;
	// printf("%d\n", check_quotes(line));
	// printf("%d\n", check_pipes(line));
	// printf("%d\n", check_redirections(line));
	// printf("%d\n\n", check_vars(line));
	if (check_quotes(line) && check_pipes(line) && check_redirections(line) && check_vars(line))
	{
		line = expand_it(line, env);
		cmds = ft_split_wq(line, '|', 0, 0);

		// printf("%d\n", check_empty_pipes(cmds));
		// printf("%d\n\n", check_in_redirections(cmds));
		// check empty splits
		// check wrong redirections
		if (check_empty_pipes(cmds) && check_in_redirections(cmds))
		{
			while (cmds[++i])
			{
				// get data and fill head
				ft_fill_it(&g_cmds, cmds[i]);
			}
		}
		else
			printf("minishell: syntax error\n");
	}
	else
		printf("minishell: syntax error\n");
}
