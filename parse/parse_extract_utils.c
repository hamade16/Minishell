/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extract_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:38:11 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 17:38:12 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_cmd	*init_for_extract(int *redir)
{
	t_cmd	*cmd;

	cmd = pmalloc(sizeof(t_cmd));
	cmd->cmd = NULL;
	cmd->options = NULL;
	cmd->is_builtin = 0;
	cmd->mini_cmd = NULL;
	*redir = 0;
	return (cmd);
}

size_t	ft_extract_it_skip(char *part, size_t j)
{
	if (part[j] == '\'' || part[j] == '"')
		j++;
	while (part[j] && ((part[j] != '<' && part[j] != '>')
			|| check_quotes_ind(part, j)))
		j++;
	return (j);
}

t_cmd	*ft_extract_it_norm(char *part, int *redir, t_norm *n, t_cmd *c)
{
	char	*filename;

	if (part[n->j] == '>' || part[n->j] == '<')
		parse_redir_macro(part, redir, &n->j);
	else
	{
		n->i = n->j;
		n->j = ft_extract_it_skip(part, n->j);
		if (c->cmd == NULL && *redir == 0)
		{
			c->cmd = ft_substr_wrap(part, n->i, n->j - n->i);
			ft_append(&c->options, ft_substr_wrap(part, n->i, n->j - n->i));
			c->is_builtin = ft_is_builtin(c->cmd);
		}
		else if (*redir)
		{
			filename = ft_substr_wrap(part, n->i, n->j - n->i);
			ft_mini_addback(&c->mini_cmd, filename, *redir, 0);
			free(filename);
			*redir = 0;
		}
		else
			ft_append(&c->options, ft_substr_wrap(part, n->i, n->j - n->i));
	}
	return (c);
}

void	ft_extract_it(t_cmd **head, char *line, int redir)
{
	size_t		i;
	t_norm		norm;
	char		**parts;
	t_cmd		*tmp;

	i = 0;
	tmp = init_for_extract(&redir);
	parts = ft_split_wq(line, ' ', 0, 0);
	while (parts[i])
	{
		norm.j = 0;
		while (parts[i][norm.j])
			tmp = ft_extract_it_norm(parts[i], &redir, &norm, tmp);
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
