/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:40:37 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 07:56:20 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_builtin(t_imp **imp)
{
	int	i;

	if (!ft_strcmp(g_global->lst->cmd, "export"))
	{
		if (g_global->lst->options[1] != NULL)
			imp = manages_options(imp);
		else
			print_export(imp);
	}
	if (!ft_strcmp(g_global->lst->cmd, "echo"))
		impecho(0);
	if (!ft_strcmp(g_global->lst->cmd, "unset"))
		imp = ft_unset(imp);
	if (!ft_strcmp(g_global->lst->cmd, "cd"))
		i = ft_cd(imp);
	if (!ft_strcmp(g_global->lst->cmd, "pwd"))
		ft_pwd(imp);
	if (!ft_strcmp(g_global->lst->cmd, "exit"))
		ft_exit();
	if (!ft_strcmp(g_global->lst->cmd, "env"))
		print_env(imp);
}
