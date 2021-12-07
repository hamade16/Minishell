/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_in_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:34:47 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 07:56:28 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ex_in_childs(t_imp **imp)
{
	int	pid;

	if (g_global->lst->is_builtin)
	{
		pid = fork();
		wait(0);
		if (pid == 0)
		{
			if (!ft_strcmp(g_global->lst->cmd, "echo"))
				impecho(0);
			if (!ft_strcmp(g_global->lst->cmd, "pwd"))
				ft_pwd(imp);
			if (!ft_strcmp(g_global->lst->cmd, "env"))
				print_env(imp);
			if (!ft_strcmp(g_global->lst->cmd, "export")
				&& (g_global->lst->options[1] == NULL))
				print_export(imp);
			exit(0);
		}
	}
	else
		ft_execve(imp);
}
