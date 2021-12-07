/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:23:47 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/06 21:09:08 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	macro_red(int red, char *file, int ambig)
{
	int	fd;

	fd = 0;
	if (red == 1)
		fd = red_out(file, ambig);
	else
		fd = red_in(file, ambig);
	return (fd);
}

int	red_out(char *filename, int ambig)
{
	int	fd;

	if (access(filename, F_OK) == 0)
	{
		if (access(filename, W_OK))
		{
			ft_error(filename,
				": Permission denied", "1");
			return (0);
		}
	}
	if (ambig == 1)
	{
		ft_error(filename,
			": ambiguous redirect", "1");
		return (0);
	}
	fd = open(filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	red_in(char *filename, int ambig)
{
	int	fd;

	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK))
		{
			ft_error(filename,
				": Permission denied", "1");
			return (0);
		}
	}
	if (ambig == 1)
	{
		ft_error(filename,
			": ambiguous redirect", "1");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fd);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

int	red_herdog(char *file, t_imp *env)
{
	int		fd;
	int		pid;
	char	*line;

	g_global->her_ex = 1;
	fd = open("/tmp/heredocfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	wait(0);
	if (pid == 0)
	{
		g_global->child_ex = 1;
		while (1)
		{
			line = readline("> ");
			if (line)
				line = expand_it(line, env);
			if (ft_strcmp(line, file))
				ft_putendl_fd(line, fd);
			else
				break ;
		}
		exit(0);
	}
	close(fd);
	return (fd);
}

int	macro_typered(int fd)
{
	t_mini_cmd	*m;

	m = g_global->lst->mini_cmd;
	while (m != NULL)
	{
		if (m->redir == 1 || m->redir == 2)
		{
			fd = macro_red(m->redir, m->filename, m->ambig);
			if (fd == 0)
				return (0);
		}
		if (m->redir == 3)
		{
			if (m->ambig == 1)
				ft_error(m->filename, ": ambiguous redirect", "1");
			else
			{
				fd = open(m->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		m = m->next_mini;
	}
	return (fd);
}
