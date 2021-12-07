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
	if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

// void	ft_extract_it_norm(char *part, char **f, int *redir, size_t *j)
// {
// 	size_t	k;

// 	k = *j;
// 	if (part[*j] == '\'' || part[*j] == '"')
// 		(*j)++;
// 	while (part[*j] && ((part[*j] != '<' && part[*j] != '>')
// 			|| check_quotes_ind(part, *j)))
// 		(*j)++;
// 	if (tmp->cmd == NULL && redirection == 0)
// 	{
// 		tmp->cmd = ft_substr_wrap(part, k, *j - k);
// 		ft_append(&tmp->options, ft_substr_wrap(part, k, *j - k));
// 		tmp->is_builtin = ft_is_builtin(tmp->cmd);
// 	}
// 	else if (redirection)
// 	{
// 		*f = ft_substr_wrap(part, k, *j - k);
// 		ft_mini_addback(&tmp->mini_cmd, *f, redirection, 0);
// 		free(*f);
// 		*f = NULL;
// 		*redir = 0;
// 	}
// 	else
// 		ft_append(&tmp->options, ft_substr_wrap(part, k, *j - k));
// }

size_t	ft_extract_it_skip(char *part, size_t j)
{
	if (part[j] == '\'' || part[j] == '"')
		j++;
	while (part[j] && ((part[j] != '<' && part[j] != '>')
			|| check_quotes_ind(part, j)))
		j++;
	return (j);
}

void	ft_extract_data(char *part, t_cmd **new)
{
	size_t	j;
	size_t	k;
	int		redir;
	char	*filename;

	j = 0;
	while (part[j])
	{
		if (part[j] == '>' || part[j] == '<')
			parse_redir_macro(part, &redir, &j);
		else
		{
			k = j;
			j = ft_extract_it_skip(part, j);
			if ((*new)->cmd == NULL && redir == 0)
			{
				(*new)->cmd = ft_substr_wrap(part, k, j - k);
				ft_append(&(*new)->options, ft_substr_wrap(part, k, j - k));
				(*new)->is_builtin = ft_is_builtin((*new)->cmd);
			}
			else if (redir)
			{
				filename = ft_substr_wrap(part, k, j - k);
				ft_mini_addback(&(*new)->mini_cmd, filename, redir, 0);
				free(filename);
				redir = 0;
			}
			else
				ft_append(&(*new)->options, ft_substr_wrap(part, k, j - k));
		}
	}
}

// TODO:
	// norm
void	ft_extract_it(t_cmd **head, char *line, char *filename, int redir)
{
	size_t		i;
	size_t		j;
	size_t		k;
	char		**parts;
	t_cmd		*tmp;

	i = 0;
	tmp = init_for_extract(&filename, &redir);
	parts = ft_split_wq(line, ' ', 0, 0);
	while (parts[i])
	{
		j = 0;
		// ft_extract_data(parts[i], &tmp);
		while (parts[i][j])
		{
			if (parts[i][j] == '>' || parts[i][j] == '<')
				parse_redir_macro(parts[i], &redir, &j);
			else
			{
				k = j;
				j = ft_extract_it_skip(parts[i], j);
				if (tmp->cmd == NULL && redir == 0)
				{
					tmp->cmd = ft_substr_wrap(parts[i], k, j - k);
					ft_append(&tmp->options, ft_substr_wrap(parts[i], k, j - k));
					tmp->is_builtin = ft_is_builtin(tmp->cmd);
				}
				else if (redir)
				{
					filename = ft_substr_wrap(parts[i], k, j - k);
					ft_mini_addback(&tmp->mini_cmd, filename, redir, 0);
					free(filename);
					redir = 0;
				}
				else
					ft_append(&tmp->options, ft_substr_wrap(parts[i], k, j - k));
			}
		}
		i++;
	}
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
	*head = tmp;
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
					ft_extract_it(&g_global->lst, line, NULL, 0);
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
