/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 03:59:44 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 08:02:08 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_imp **imp)
{
	char	buff[1000];
	t_imp	*tmp;

	tmp = *imp;
	while (tmp != NULL)
	{
		if (!ft_strcmp((tmp)->key, "PWD"))
		{
			printf("%s\n", (tmp)->value);
			break ;
		}
		tmp = (tmp)->next;
	}
	if (tmp == NULL)
		printf("%s\n", getcwd(buff, 100));
}
