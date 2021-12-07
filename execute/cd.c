/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:13:55 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 04:31:16 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	old_pwd(t_imp **imp)
{
	t_imp	*tmp;
	char	*str;
	char	buff[100];

	tmp = *imp;
	while (tmp && ft_strcmp(tmp->key, "PWD"))
		tmp = tmp->next;
	if (tmp != NULL)
	{
		str = tmp->value;
		tmp->value = ft_strdup(getcwd(buff, 100));
	}
	tmp = *imp;
	while (tmp && ft_strcmp(tmp->key, "OLDPWD"))
		tmp = tmp->next;
	if (tmp != NULL)
		tmp->value = str;
}

int	cd_no_opt(t_imp **imp)
{
	t_imp	*tmp;

	tmp = *imp;
	while ((tmp != NULL) && ft_strcmp(tmp->key, "HOME"))
		tmp = tmp->next;
	if (tmp == NULL)
	{
		ft_putstr_fd(": cd: HOME not set\n", 2);
		g_global->error = "1";
		return (0);
	}
	else
	{
		if (chdir(tmp->value) == -1)
		{
			ft_error(tmp->value, ": No such file or directory", "1");
			return (0);
		}
		old_pwd(imp);
		return (0);
	}
	return (1);
}

int	cd_macro(t_imp **imp)
{
	if (g_global->lst->options[1] == NULL)
	{
		if (cd_no_opt(imp) == 0)
			return (0);
	}
	else if (chdir(g_global->lst->options[1]) == -1)
	{
		ft_error(g_global->lst->options[1], ": No such file or directory", "1");
		return (0);
	}
	return (1);
}

int	ft_cd(t_imp **imp)
{
	t_imp	*tmp;
	char	*str;
	char	buff[100];

	tmp = *imp;
	str = ft_strdup("");
	if (cd_macro(imp) == 0)
		return (0);
	tmp = *imp;
	while (tmp && ft_strcmp(tmp->key, "PWD"))
		tmp = tmp->next;
	if (tmp != NULL)
	{
		str = tmp->value;
		tmp->value = ft_strdup(getcwd(buff, 100));
	}
	tmp = *imp;
	while (tmp && ft_strcmp(tmp->key, "OLDPWD"))
		tmp = tmp->next;
	if (tmp != NULL)
	{
		tmp->value = str;
		free(str);
	}
	return (0);
}
