/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:40:20 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/06 12:27:18 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	valid_env_n(int i)
{
	int	j;

	j = 0;
	while (g_global->lst->options[i][j])
	{
		if ((g_global->lst->options[i][j] != '_'
			&& !ft_isalnum(g_global->lst->options[i][j]))
				|| (g_global->lst->options[i][0] != '_'
					&& !ft_isalpha(g_global->lst->options[i][0])))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(g_global->lst->options[i], 2);
			ft_putstr_fd("\' : not a valid identifier\n", 2);
			g_global->error = "1";
			break ;
		}
		j++;
	}
}

void	clear_node(t_imp **imp, int i)
{
	t_imp	*tmp;
	t_imp	*prev;

	tmp = *imp;
	while (tmp != NULL
		&& ft_strcmp(tmp->key, g_global->lst->options[i]))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		prev->next = tmp->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
	}
}

t_imp	**ft_unset(t_imp **imp)
{
	t_imp	*tmp;
	int		i;

	i = 1;
	if (g_global->lst->options[1] == NULL)
		return (imp);
	while (g_global->lst->options[i])
	{
		valid_env_n(i);
		if (!(ft_strcmp((*imp)->key, g_global->lst->options[i])))
		{
			tmp = *imp;
			(*imp) = (*imp)->next;
			free(tmp->value);
			free(tmp->key);
			free(tmp);
		}
		else
			clear_node(imp, i);
		i++;
	}
	return (imp);
}
