/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:40:20 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/05 19:51:35 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (!(ft_strcmp((*imp)->key, g_global->lst->options[i])))
		{
			tmp = *imp;
			(*imp) = (*imp)->next;
			free(tmp);
		}
		else
			clear_node(imp, i);
		i++;
	}
	return (imp);
}
