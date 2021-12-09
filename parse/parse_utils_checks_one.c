/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_checks_one.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:12:15 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:12:17 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_forbidden(char *s)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		quote = quote_macro(s[i], quote);
		if ((s[i] == '|' || s[i] == ';' || s[i] == '\\') && quote == 0)
		{
			g_global->error = "259";
			ft_putstr_fd("forbidden character\n", 0);
			return (0);
		}
	}
	return (1);
}

// TODO
	// unquote then check last pipe
/*
 * double pipes
 * pipe is the last thing (not quoted)
 */
int	check_pipes(char *l)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (l[++i])
	{
		quote = quote_macro(l[i], quote);
		if (l[i] == '|' && quote == 0)
		{
			if (l[i + 1] == '|')
			{
				g_global->error = "259";
				ft_putstr_fd("minishell: forbidden character\n", 0);
				return (0);
			}
		}
	}
	return (1);
}

/*
 * on error 0
 * on success 1
 */
int	check_vars(char *s)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		quote = quote_macro(s[i], quote);
		if (s[i] == '$' && quote != 1)
		{
			if (s[i + 1] != '?' && s[i + 1] != '_' && !ft_isalpha(s[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_empty_pipes(char **cmds)
{
	size_t	i;
	size_t	j;
	int		flag;

	i = -1;
	while (cmds[++i])
	{
		j = -1;
		flag = 0;
		while (cmds[i][++j])
		{
			if (cmds[i][j] != ' ')
				flag = 1;
		}
		if (!flag)
			return (0);
	}
	return (1);
}
