/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:23:47 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/05 02:35:45 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_out(void)
{
	int	fd;

	if (access(g_global->lst->mini_cmd->filename, F_OK) == 0)
	{
		if (access(g_global->lst->mini_cmd->filename, W_OK))
		{
			ft_error(g_global->lst->mini_cmd->filename,
				": Permission denied", "1");
			return (0);
		}
	}
	if (g_global->lst->mini_cmd->ambig == 1)
	{
		ft_error(g_global->lst->mini_cmd->filename,
			": ambiguous redirect", "1");
		return (0);
	}
	fd = open(g_global->lst->mini_cmd->filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2 (fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	red_in(void)
{
	int fd;

	if (access(g_global->lst->mini_cmd->filename, F_OK) == 0)
	{
		if (access(g_global->lst->mini_cmd->filename, R_OK))
		{
			ft_error(g_global->lst->mini_cmd->filename,
				": Permission denied", "1");
			return (0);
		}
	}
	fd = open(g_global->lst->mini_cmd->filename, O_RDONLY);
	if (fd < 0)
		return (fd);
   	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}
/*
int	red_herdog(t_mini_cmd *c)
{
	int fd;
	int pid;
	
	g_global->her_ex = 1;
	fd = open("/tmp/heredocfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
	{
		g_global->child_ex = 1;
		while (1)
		{
			char *line;
			line = readline("> ");
			if (ft_strcmp(line, c->filename))
				ft_putendl_fd(line, fd);
			else
				break;
		}
		exit(0);
	}
	close(fd);
	if (pid != 0)
		wait(0);
	return (fd);
}
*/
