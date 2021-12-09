/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:13:48 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:13:49 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_it_init(size_t *a, size_t *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int	expand_it_cmp_macro(char *s, size_t i, int quote)
{
	if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_'
			|| s[i + 1] == '?') && quote != 1)
		return (1);
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

void	expand_cmp_iter_macro(char *s, size_t *i, size_t *size)
{
	if (s[*i])
	{
		(*size)++;
		(*i)++;
	}
}

char	*expand_it(char *s, t_imp *env, size_t size)
{
	t_norm	norm;
	int		quote;
	char	*res;

	expand_it_init(&norm.i, &size, &quote);
	while (s[norm.i])
	{
		quote = quote_macro(s[norm.i], quote);
		if (expand_it_cmp_macro(s, norm.i, quote))
			expand_it_count(s, &norm.i, &size, env);
		expand_cmp_iter_macro(s, &norm.i, &size);
	}
	expand_it_init(&norm.i, &norm.j, &quote);
	res = pmalloc(sizeof(char) * size + 1);
	while (s[norm.i])
	{
		quote = quote_macro(s[norm.i], quote);
		if (expand_it_cmp_macro(s, norm.i, quote))
			norm = expand_it_repl(s, norm, &res, env);
		else
			expand_repl_iter_macro(s, &res, &norm.i, &norm.j);
	}
	res[norm.j] = '\0';
	return (res);
}
