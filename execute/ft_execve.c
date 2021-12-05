/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:39:56 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/05 03:36:55 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*path_env(struct imp **imp)
{
	int			i;
	struct imp	*tmp;

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

char	*research_path(struct imp **imp)
{
	char	**path;
	char	*pathname;
	int		i;

	i = 0;
	if (access(g_global->lst->cmd, F_OK) == 0 && g_global->lst->cmd[0] == '/')
		return (ft_strdup(g_global->lst->cmd));
	if (!path_env(imp))
		return ("uns_path");
	path = ft_split(path_env(imp), ':');
	while (path[i])
	{
		pathname = ft_strjoin_char(path[i], g_global->lst->cmd, '/');
		if (access(pathname, F_OK) == 0)
			break ;
		i++;
		free(pathname);
	}
	if (path[i] == NULL)
		return (NULL);
	ft_free_split(path);
	return (pathname);
}

int	ft_execve(struct imp **imp)
{
	char	**env_conv;
	int		acces;
	int		inacces;

	env_conv = ft_convert_to_arr(*imp);
	if (access((g_global->lst->cmd), F_OK) == 0
		&& g_global->lst->cmd[0] == '.' && g_global->lst->cmd[1] == '/')
	{
		acces = is_execitable(env_conv);
		if (acces == 0)
			return (0);
	}
	else
	{
		inacces = inexecutable(imp, env_conv);
		if (inacces == 0)
			return (0);
	}
	return (1);
}
