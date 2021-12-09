/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_utils_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:34:08 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 15:34:11 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_it_repl_norm(char *s, size_t *i, size_t *var_size)
{
	if (s[*i - 1] != '?')
	{
		while (ft_isalnum(s[*i]) || s[*i] == '_')
		{
			(*i)++;
			(*var_size)++;
		}
	}
}

t_norm	expand_it_repl(char *s, t_norm norm, char **res, t_imp *head)
{
	size_t	var_size;
	char	*var_key;

	norm.i += 2;
	var_size = 2;
	expand_it_repl_norm(s, &norm.i, &var_size);
	var_key = ft_substr_wrap(s, norm.i - var_size + 1, var_size - 1);
	while (head)
	{
		if (ft_strcmp(var_key, head->key) == 0)
		{
			ft_strlcpy(*res + norm.j, head->value, ft_strlen(head->value) + 1);
			norm.j += ft_strlen(head->value);
		}
		head = head->next;
	}
	if (ft_strcmp(var_key, "?") == 0)
	{
		ft_strlcpy(*res + norm.j, g_global->error,
			ft_strlen(g_global->error) + 1);
		norm.j += ft_strlen(g_global->error);
	}
	free(var_key);
	return (norm);
}

void	expand_repl_iter_macro(char *s, char **res, size_t *i, size_t *j)
{
	(*res)[*j] = s[*i];
	(*j)++;
	(*i)++;
}

size_t	expand_it_one_norm(char *key_var, char *key_lst, char *val_lst)
{
	if (ft_strcmp(key_var, key_lst) == 0)
		return (ft_strlen(val_lst));
	return (0);
}

void	ft_expand_data(t_cmd **cmd, t_imp *env)
{
	int			i;
	t_mini_cmd	*mini;

	if ((*cmd)->cmd)
	{
		(*cmd)->cmd = ft_expand_cmd((*cmd)->cmd, env);
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
