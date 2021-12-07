/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:07:10 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/06 23:22:21 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo_mac(int i)
{
	printf("%s", g_global->lst->options[i]);
	if (g_global->lst->options[i + 1])
		printf(" ");
}

void	print_echo(int i)
{
	while (g_global->lst->options[i])
	{
		printf("%s", g_global->lst->options[i]);
		if (g_global->lst->options[i + 1])
			printf(" ");
		i++;
	}
}

int	echo_macro_if(int i, int j)
{
	return (g_global->lst->options[i][j] == '-'
			&& g_global->lst->options[i][j + 1] == 'n');
}

void	echo(int i, int j)
{
	while (g_global->lst->options[i])
	{
		j = 0;
		if (echo_macro_if(i, j))
		{
			j++;
			while (g_global->lst->options[i][j]
				&& g_global->lst->options[i][j] == 'n')
				j++;
			if (g_global->lst->options[i][j])
			{
				i--;
				while (g_global->lst->options[++i])
					print_echo_mac(i);
				break ;
			}
			else
				i++;
		}
		else
		{
			print_echo(i);
			break ;
		}
	}
}

void	impecho(int j)
{
	if (!g_global->lst->options[1])
		printf("\n");
	echo(1, 0);
	if (g_global->lst->options[1])
	{
		if (g_global->lst->options[1][j] == '-')
		{
			j++;
			if (!g_global->lst->options[1][j])
				printf("\n");
			while (g_global->lst->options[1][j])
			{
				if (g_global->lst->options[1][j] != 'n')
				{
					printf("\n");
					break ;
				}
				j++;
			}
		}
		else
			printf("\n");
	}
}
