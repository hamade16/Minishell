/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:41:47 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 06:53:39 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	macro_1(int wstatus)
{
	if (WTERMSIG(wstatus) == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		g_global->error = "131";
	}
}

void	macro_2(int wstatus)
{
	int	statuscode;
	DIR	*directory;

	statuscode = WEXITSTATUS(wstatus);
	if (statuscode != 0)
	{
		directory = opendir(g_global->lst->cmd);
		if (directory)
			ft_error(g_global->lst->cmd, ": is a directory", "127");
		else
			g_global->error = "1";
		
	}
}

int	is_execitable(char **env_conv)
{
	int	pid;
	int	wstatus;
	int	i;

	if (access((g_global->lst->cmd), X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			i = execve(g_global->lst->cmd, g_global->lst->options, env_conv);
			exit(i);
		}
		else
		{
			waitpid(pid, &wstatus, 0);
			is_file(wstatus);
		}
	}
	else
	{
		ft_error(g_global->lst->cmd, ": Permission denied", "126");
		return (0);
	}
	return (1);
}

void	ex_execve(char *pathname, char **env_conv)
{
	int	pid;
	int	wstatus;
	int	i;

	pid = fork();
	g_global->her_ex = 1;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		g_global->child_ex = 1;
		i = execve(pathname, g_global->lst->options, env_conv);
		exit(i);
	}
	else
	{
		g_global->child_ex = 0;
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			macro_2(wstatus);
		if (WIFSIGNALED(wstatus))
			macro_1(wstatus);
	}
}

int	inexecutable(t_imp **imp, char **env_conv)
{
	char	*pathname;

	pathname = research_path(imp);
	if ((pathname == NULL) && ft_strchr(g_global->lst->cmd, '/'))
	{
		ft_error(g_global->lst->cmd, ": No such file or directory", "127");
		return (0);
	}
	if (pathname == NULL)
	{
		ft_error(g_global->lst->cmd, ": command not found", "127");
		return (0);
	}
	if (!ft_strcmp(pathname, "uns_path"))
		return (0);
	ex_execve(pathname, env_conv);
	g_global->her_ex = 0;
	if (pathname)
		free(pathname);
	return (1);
}
