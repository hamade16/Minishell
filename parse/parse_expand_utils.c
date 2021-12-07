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
