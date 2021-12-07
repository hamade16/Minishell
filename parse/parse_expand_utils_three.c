/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_utils_three.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:14:03 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:14:05 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_norm(char *str, t_imp *env)
{
	char	*tmp;

	tmp = str;
	str = expand_it(str, env, 0);
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

size_t	expand_it_one_norm(char *key_var, char *key_lst, char *val_lst)
{
	if (ft_strcmp(key_var, key_lst) == 0)
		return (ft_strlen(val_lst));
	return (0);
}

void	expand_it_count(char *s, size_t *i, size_t *size, t_imp *head)
{
	size_t	var_size;
	char	*var_key;

	(*i) += 2;
	var_size = 2;
	if (s[(*i) - 1] != '?')
	{
		while (ft_isalnum(s[*i]) || s[*i] == '_')
		{
			(*i)++;
			var_size++;
		}
	}
	var_key = ft_substr_wrap(s, *i - var_size + 1, var_size - 1);
	while (head)
	{
		(*size) += expand_it_one_norm(var_key, head->key, head->value);
		head = head->next;
	}
	if (ft_strcmp(var_key, "?") == 0)
		(*size) += ft_strlen(g_global->error);
	free(var_key);
}
