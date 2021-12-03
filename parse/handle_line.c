#include "../execute/minishell_execute.h"
#include "../minishell.h"

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
			len++;
		tmp = *opt;
		*opt = malloc(sizeof(char *) * (len + 1 + 1));
		i = -1;
		while (++i < len)
			(*opt)[i] = tmp[i];
		free(tmp);
		(*opt)[i] = newopt;
		(*opt)[i + 1] = NULL;
	}
}

// TODO:
	// norm
void	ft_fill_it(t_cmd **head, char *line)
{
	size_t		i;
	size_t		j;
	size_t		k;
	char		**parts;
	t_cmd		*tmp;
	t_mini_cmd	*mini;
	char		*filename;
	int			redirection;

	i = 0;

	tmp = malloc(sizeof(t_cmd));

	tmp->text = ft_strdup(line);
	tmp->cmd = NULL;
	tmp->options = NULL;
	tmp->is_builtin = 0;
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
					redirection = 1;
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
					redirection = 2;
				j++;
			}
			else
			{
				k = j;
				// TODO
				if (parts[i][j] == '\'' || parts[i][j] == '"')
					j++;
				while (parts[i][j] && ((parts[i][j] != '<' && parts[i][j] != '>') || check_quotes_ind(parts[i], j)))
					j++;
				if (tmp->cmd == NULL && redirection == 0)
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
					ft_append(&tmp->options, ft_substr(parts[i], k, j - k));
			}
		}
		i++;
	}
	tmp->next_cmd = NULL;
	if (*head == NULL)
		*head = tmp;
	else
	{
		free(*head);
		*head = tmp;
	}
}

// TODO:
	// norm
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
	quote = 0;
	var_size = 0;
	var_key = NULL;
	res = NULL;
	while (s[i])
	{
		quote = quote_macro(s[i], quote);
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
		{
			i += 2;
			var_size += 2;
			if (s[i - 1] != '?')
				while (ft_isalnum(s[i]))
				{
					i++;
					var_size++;
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
			if (ft_strcmp(var_key, "?") == 0)
			{
				size += ft_strlen(g_global->error);
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
	quote = 0;
	var_size = 0;
	res = malloc(sizeof(char) * size + 1);
	while (s[i])
	{
		quote = quote_macro(s[i], quote);
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
		{
			i += 2;
			var_size += 2;
			if (s[i - 1] != '?')
				while (ft_isalnum(s[i]))
				{
					i++;
					var_size++;
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
			if (ft_strcmp(var_key, "?") == 0)
			{
				ft_strlcpy(res+j, g_global->error, ft_strlen(g_global->error) + 1);
				j += ft_strlen(g_global->error);
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

int	contains_quotes(char *s)
{
	size_t	i;
	int		len;
	int		quote;

	i = -1;
	len = 0;
	quote = 0;
	while (s[++i])
	{
		if (s[i] == '\'' && quote == 0)
		{
			quote = 1;
			len++;
		}
		else if (s[i] == '"' && quote == 0)
		{
			quote = 2;
			len++;
		}
		else if (s[i] == '\'' == quote == 1)
			quote = 0;
		else if (s[i] == '"' && quote == 2)
			quote = 0;
	}
	return (len);
}

char	*ft_remove_quotes(char *str)
{
	size_t	i;
	size_t	j;
	int		quote;
	char	*new;

	i = 0;
	j = 0;
	quote = 0;
	new = malloc(sizeof(char) * (ft_strlen(str)
				- contains_quotes(str) * 2 + 1));
	while (str[i])
	{
		quote = quote_macro(str[i], quote);
		if (!((str[i] == '\'' && quote != 2) || (str[i] == '"' && quote != 1)))
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	ft_unquote(t_cmd **cmd)
{
	int			i;
	char		*tmp;
	t_mini_cmd	*mini;

	tmp = (*cmd)->cmd;
	if ((*cmd)->cmd)
		(*cmd)->cmd = ft_remove_quotes((*cmd)->cmd);
	free(tmp);
	i = 0;
	if ((*cmd)->options)
		while ((*cmd)->options[i])
		{
			tmp = (*cmd)->options[i];
			(*cmd)->options[i] = ft_remove_quotes((*cmd)->options[i]);
			free(tmp);
			i++;
		}
	mini = (*cmd)->mini_cmd;
	while (mini)
	{
		if (mini->filename)
		{
			tmp = mini->filename;
			mini->filename = ft_remove_quotes(mini->filename);
			free(tmp);
			i++;
		}
		mini = mini->next_mini;
	}
}

// TODO:
	// ambiguous redirect error
	// echo $"abc"
void	handle_line(char *line, struct imp *env)
{
	// '|', ';'
	if (check_forbidden(line))
	{
		if (check_quotes(line) && check_redirections(line))
		{
			line = expand_it(line, env);
			if (check_in_redirections(line))
			{
				// get data and fill head
				ft_fill_it(&g_global->lst, line);
				ft_unquote(&g_global->lst);
				g_global->error = "0";
			}
			else
				g_global->error = "258";
		}
		else
			g_global->error = "258";
	}
	else
		g_global->error = "259";
	if (!ft_strcmp(g_global->error, "258"))
		printf("minishell: syntax error\n");
	else if (!ft_strcmp(g_global->error, "259"))
		printf("minishell: forbidden character\n");
}
