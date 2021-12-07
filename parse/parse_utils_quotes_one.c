/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_quotes_one.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:14:19 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:14:21 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_macro(char c, int q)
{
	if (c == '\'' && q == 0)
		return (1);
	else if (c == '"' && q == 0)
		return (2);
	else if (c == '\'' == q == 1)
		return (0);
	else if (c == '"' && q == 2)
		return (0);
	return (q);
}

/*
 * 0	: Quotes are enclosed
 * else	: Quotes are not enclosed
 */
int	check_quotes(char *s)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		quote = quote_macro(s[i], quote);
	}
	if (quote != 0)
	{
		g_global->error = "256";
		ft_putstr_fd("minishell: unclosed quotes\n", 0);
	}
	return (!quote);
}

int	check_quotes_ind(char *s, size_t len)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (s[++i] && i < len + 1)
	{
		quote = quote_macro(s[i], quote);
	}
	return (quote);
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
	new = pmalloc(sizeof(char) * (ft_strlen(str)
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
