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

int	expand_it_cmp_macro(char *s, size_t i, int quote)
{
	if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_'
			|| s[i + 1] == '?') && quote != 1)
		return (1);
	return (0);
}

void	expand_cmp_iter_macro(char *s, size_t *i, size_t *size)
{
	if (s[*i])
	{
		(*size)++;
		(*i)++;
	}
}

void	expand_repl_iter_macro(char *s, char **res, size_t *i, size_t *j)
{
	(*res)[*j] = s[*i];
	(*j)++;
	(*i)++;
}
