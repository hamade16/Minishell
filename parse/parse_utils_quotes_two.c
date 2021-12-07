/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_quotes_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:12:45 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:12:47 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remove_quotes_norm(char *str)
{
	char	*tmp;

	tmp = str;
	str = ft_remove_quotes(str);
	free(tmp);
	return (str);
}

void	ft_unquote(t_cmd **cmd)
{
	int			i;
	t_mini_cmd	*mini;

	if ((*cmd)->cmd)
		(*cmd)->cmd = ft_remove_quotes_norm((*cmd)->cmd);
	i = 0;
	if ((*cmd)->options)
	{
		while ((*cmd)->options[i])
		{
			(*cmd)->options[i] = ft_remove_quotes_norm((*cmd)->options[i]);
			i++;
		}
	}
	mini = (*cmd)->mini_cmd;
	while (mini)
	{
		if (mini->filename)
		{
			mini->filename = ft_remove_quotes_norm(mini->filename);
			i++;
		}
		mini = mini->next_mini;
	}
}
