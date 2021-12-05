/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:11:53 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/05 15:52:49 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_imp **imp)
{
	t_imp	*tmp;

	tmp = *imp;
	while (tmp != NULL)
	{
		if (tmp->egale == 1)
		{
			if (tmp->value != NULL)
			{
				printf("%s", tmp->key);
				printf ("=");
				printf("%s", tmp->value);
				printf("\n");
			}
			else
			{
				printf("%s", tmp->key);
				printf ("=");
				printf("\n");
			}
		}
		tmp = tmp->next;
	}
}
