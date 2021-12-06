#include "../execute/minishell_execute.h"
#include "../minishell.h"

void	ft_append(char ***opt, char *newopt)
{
	size_t	i;
	size_t	len;
	char	**tmp;

	if (*opt == NULL)
	{
		*opt = pmalloc(sizeof(char *) * 2);
		(*opt)[0] = newopt;
		(*opt)[1] = NULL;
	}
	else
	{
		len = 0;
		while ((*opt)[len])
			len++;
		tmp = *opt;
		*opt = pmalloc(sizeof(char *) * (len + 1 + 1));
		i = -1;
		while (++i < len)
			(*opt)[i] = tmp[i];
		free(tmp);
		(*opt)[i] = newopt;
		(*opt)[i + 1] = NULL;
	}
}

void	parse_redir_macro(char *str, int *redir, size_t *i)
{
	if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			*redir = 3;
			(*i)++;
		}
		else
			*redir = 1;
		(*i)++;
	}
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			*redir = 4;
			(*i)++;
		}
		else
			*redir = 2;
		(*i)++;
	}
}

t_cmd	*init_for_extract(char **f, int *redir)
{
	t_cmd	*cmd;

	cmd = pmalloc(sizeof(t_cmd));
	cmd->cmd = NULL;
	cmd->options = NULL;
	cmd->is_builtin = 0;
	cmd->mini_cmd = NULL;
	*f = NULL;
	*redir = 0;
	return (cmd);
}

int	ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return(1);
	else
		return (0);
}

// TODO:
	// norm
void	ft_extract_it(t_cmd **head, char *line)
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
	tmp = init_for_extract(&filename, &redirection);
	parts = ft_split_wq(line, ' ', 0, 0);
	while (parts[i])
	{
		j = 0;
		while (parts[i][j])
		{
			if (parts[i][j] == '>' || parts[i][j] == '<')
				parse_redir_macro(parts[i], &redirection, &j);
			else
			{
				k = j;
				if (parts[i][j] == '\'' || parts[i][j] == '"')
					j++;
				while (parts[i][j] &&
					((parts[i][j] != '<' && parts[i][j] != '>')
						|| check_quotes_ind(parts[i], j)))
					j++;
				if (tmp->cmd == NULL && redirection == 0)
				{
					tmp->cmd = ft_substr_wrap(parts[i], k, j - k);
					ft_append(&tmp->options, ft_substr_wrap(parts[i], k, j - k));
					tmp->is_builtin = ft_is_builtin(tmp->cmd);
				}
				else if (redirection)
				{
					filename = ft_substr_wrap(parts[i], k, j - k);
					if (tmp->cmd == NULL)
						ft_exit_malloc();
					ft_mini_addback(&tmp->mini_cmd, filename, redirection, 0);
					free(filename);
					filename = NULL;
					redirection = 0;
				}
				else
					ft_append(&tmp->options, ft_substr_wrap(parts[i], k, j - k));
			}
		}
		i++;
	}
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
	if (*head)
	{
		if ((*head)->cmd)
			free((*head)->cmd);
		if ((*head)->options)
		{
			i = 0;
			while ((*head)->options[i])
			{
				free((*head)->options[i]);
				i++;
			}
		}
		while ((*head)->mini_cmd)
		{
			mini = (*head)->mini_cmd;
			free((*head)->mini_cmd->filename);
			(*head)->mini_cmd = (*head)->mini_cmd->next_mini;
			free(mini);
		}
		free(*head);
	}
	*head = tmp;
}

char	*ft_expand_norm(char *str, t_imp *env)
{
	char	*tmp;

	tmp = str;
	str = expand_it(str, env);
	free(tmp);
	return (str);
}

void	ft_expand_data(t_cmd **cmd, t_imp *env)
{
	int			i;
	t_mini_cmd	*mini;

	if ((*cmd)->cmd)
	{
		(*cmd)->cmd = ft_expand_norm((*cmd)->cmd, env);
	}
	if ((*cmd)->options)
	{
		i = 0;
		while ((*cmd)->options[i])
		{
			(*cmd)->options[i] = ft_expand_norm((*cmd)->options[i], env);
			i++;
		}
	}
	mini = (*cmd)->mini_cmd;
	while (mini)
	{
		mini->filename = ft_expand_norm(mini->filename, env);
		if (ft_strlen(mini->filename) <= 0)
			mini->ambig = 1;
		mini = mini->next_mini;
	}
}

// TODO:
	// norm
char	*expand_it(char *s, t_imp *env)
{          
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	var_size;
	int		quote;
	char	*res;
	char	*var_key;
	t_imp *head;

	i = 0;
	size = 0;
	quote = 0;
	var_size = 0;
	var_key = NULL;
	res = NULL;
	while (s[i])
	{
		quote = quote_macro(s[i], quote);
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?') && quote != 1)
		{
			i += 2;
			var_size += 2;
			if (s[i - 1] != '?')
				while (ft_isalnum(s[i]))
				{
					i++;
					var_size++;
				}
			var_key = ft_substr_wrap(s, i - var_size + 1, var_size - 1);
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
			free(var_key);
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
	res = pmalloc(sizeof(char) * size + 1);
	while (s[i])
	{
		quote = quote_macro(s[i], quote);
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?') && quote != 1)
		{
			i += 2;
			var_size += 2;
			if (s[i - 1] != '?')
				while (ft_isalnum(s[i]))
				{
					i++;
					var_size++;
				}
			var_key = ft_substr_wrap(s, i - var_size + 1, var_size - 1);
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
			free(var_key);
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

void	handle_line(char *line, t_imp *env)
{
	if (line)
	{
		if (check_forbidden(line))
		{
			if (check_quotes(line))
			{
				if (check_redirections(line) && check_end_redirections(line))
				{
					ft_extract_it(&g_global->lst, line);
					ft_expand_data(&g_global->lst, env);
					ft_unquote(&g_global->lst);
					g_global->error = "0";
				}
				else
				{
					g_global->error = "258";
					ft_putstr_fd("minishell: syntax error\n", 0);
				}
			}
		}
	}
}
