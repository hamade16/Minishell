/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 04:34:43 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/08 20:50:55 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	macro_exit(void)
{
	int	i;

	i = 0;
	if (g_global->lst->options[1][0] == '-')
		i++;
	while (g_global->lst->options[1][i])
	{
		if (!ft_isdigit(g_global->lst->options[1][i]))
		{
			error_exit(g_global->lst->options[1]);
			exit(255);
		}
		i++;
	}
}

void	ft_exit(void)
{
	unsigned char	e;

	if (g_global->sig_exdeja == 1)
		printf("exit");
	else
		printf("exit\n");
	if (g_global->lst->options[1])
		macro_exit();
	if (g_global->lst->options[1] == NULL)
		exit(EXIT_SUCCESS);
	else if (g_global->lst->options[2])
		printf("minishell: too many arguments\n");
	else
	{
		e = ft_atoi(g_global->lst->options[1]);
		exit(e);
	}
}
