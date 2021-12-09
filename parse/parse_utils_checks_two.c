/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_checks_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:12:24 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:12:26 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redirections_macro(char *s, int i)
{
	if (s[i] == '>')
	{
		if (s[i + 1] == '<')
			return (0);
		if (s[i + 1] == '>')
			if (s[i + 2] == '>')
				return (0);
	}
	else if (s[i] == '<')
	{
		if (s[i + 1] == '>')
			return (0);
		if (s[i + 1] == '<')
			if (s[i + 2] == '<')
				return (0);
	}
	return (1);
}

void	init_check_redirection(size_t *i, int *quote, int *right, int *left)
{
	*i = -1;
	*quote = 0;
	*right = 0;
	*left = 0;
}

int	check_redir_helper(char *s, size_t i, int *right, int *left)
{
	if (s[i] == '>')
	{
		if (s[i - 1] == ' ' && (*left > 0 || *right > 0))
			(*right) += 2;
		(*right)++;
	}
	else if (s[i] == '<')
	{
		if (s[i - 1] == ' ' && (*left > 0 || *right > 0))
			(*left) += 2;
		(*left)++;
	}
	else if (s[i] != ' ')
	{
		*right = 0;
		*left = 0;
	}
	if (*right > 2 || *left > 2 || (*left > 0 && *right > 0))
		return (0);
	return (1);
}

/*
 * check some errors
 * <>, ><, <<>, >><, <<<, >>>
 * on error 0
 * on success 1
 */
int	check_redirections(char *s)
{
	size_t	i;
	int		quote;
	int		right;
	int		left;

	init_check_redirection(&i, &quote, &right, &left);
	while (s[++i])
	{
		quote = quote_macro(s[i], quote);
		if (quote == 0)
		{
			if (check_redir_helper(s, i, &right, &left) == 0)
				return (0);
		}
	}
	return (1);
}

/*
 * redirection at the end
 */
int	check_end_redirections(char *cmd)
{
	char	*trimmd;
	size_t	len;
	int		flag;

	flag = 1;
	trimmd = ft_strtrim(cmd, " ");
	len = ft_strlen(trimmd);
	if (len > 0 && (trimmd[len - 1] == '<' || trimmd[len - 1] == '>'))
		flag = 0;
	free(trimmd);
	return (flag);
}
