/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:13:04 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:13:08 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mini_cmd	*ft_mini_lstlast(t_mini_cmd *lst)
{
	if (lst)
		while (lst->next_mini)
			lst = lst->next_mini;
	return (lst);
}

void	ft_mini_addback(t_mini_cmd **head, char *f, int r, int a)
{
	t_mini_cmd	*last;
	t_mini_cmd	*new;

	new = pmalloc(sizeof(t_mini_cmd));
	new->filename = ft_strdup_wrap(f);
	new->redir = r;
	new->ambig = a;
	new->next_mini = NULL;
	if (head && new)
	{
		if (*head)
		{
			last = ft_mini_lstlast(*head);
			last->next_mini = new;
		}
		else
			*head = new;
	}
}
