/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:39:56 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 09:40:40 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_file(int wstatus)
{
	int	statuscode;
	DIR	*directory;

	if (WIFEXITED(wstatus))
	{
		statuscode = WEXITSTATUS(wstatus);
		if (statuscode != 0)
		{
			directory = opendir(g_global->lst->cmd);
			if (directory)
				ft_error(g_global->lst->cmd, ": is a directory", "127");
		}
	}
}

char	*ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	*path_env(t_imp **imp)
{
	int			i;
	t_imp		*tmp;

	i = 0;
	tmp = *imp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		ft_error(g_global->lst->cmd,
			": No such file or directory", "127");
		return (0);
	}
	return (tmp->value);
}

char	*research_path(t_imp **imp)
{
	char	**path;
	int		i;

	i = 0;
	g_global->pathname = NULL;
	if (access(g_global->lst->cmd, F_OK) == 0 && g_global->lst->cmd[0] == '/')
		return (ft_strdup_wrap(g_global->lst->cmd));
	if (!path_env(imp))
		return ("uns_path");
	path = ft_split(path_env(imp), ':');
	while (path[i])
	{
		g_global->pathname = ft_strjoin_char(path[i], g_global->lst->cmd, '/');
		if (access(g_global->pathname, F_OK) == 0)
			break ;
		i++;
		free(g_global->pathname);
		g_global->pathname = NULL;
	}
	ft_free_split(path);
	return (g_global->pathname);
}

int	ft_execve(t_imp **imp)
{
	char	**env_conv;
	int		acces;
	int		inacces;

	env_conv = ft_convert_to_arr(*imp);
	if (access((g_global->lst->cmd), F_OK) == 0
		&& g_global->lst->cmd[0] == '.'
		&& g_global->lst->cmd[1] == '/')
	{
		acces = is_execitable(env_conv);
		free_double(env_conv);
		if (acces == 0)
			return (0);
	}
	else
	{
		inacces = inexecutable(imp, env_conv);
		free_double(env_conv);
		if (inacces == 0)
			return (0);
	}
	return (1);
}
