/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:52:56 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 22:57:02 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_file(int fd, int tmp_fd_out, int tmp_fd_in)
{
	if (fd < 0)
	{
		dup2(tmp_fd_out, STDOUT_FILENO);
		ft_error(g_global->lst->mini_cmd->filename,
			": No such file or directory", "1");
		dup_red(tmp_fd_out, tmp_fd_in);
		return (0);
	}
	if (fd == 0)
	{
		dup_red(tmp_fd_out, tmp_fd_in);
		return (0);
	}
	return (1);
}

void	ex_with_redriction(t_imp **imp)
{
	if (!ft_strcmp(g_global->lst->cmd, "export")
		&& g_global->lst->options && g_global->lst->options[1] != NULL)
		imp = manages_options(imp);
	if (!ft_strcmp(g_global->lst->cmd, "cd"))
		ft_cd(imp);
	if (!ft_strcmp(g_global->lst->cmd, "unset"))
		ft_unset(imp);
	if (!ft_strcmp(g_global->lst->cmd, "exit"))
		ft_exit();
	else
		ex_in_childs(imp);
}

void	dup_red(int a, int b)
{
	dup2(a, STDOUT_FILENO);
	dup2(b, STDIN_FILENO);
}

int	type_redirection(int fd, t_imp *env)
{
	int			heredoc;
	t_mini_cmd	*c;

	c = g_global->lst->mini_cmd;
	heredoc = 0;
	while (c)
	{
		if (c->redir == 4)
		{
			heredoc = 1;
			red_herdog(c->filename, env);
			c = c->next_mini;
		}
		else
			c = c->next_mini;
	}
	if (heredoc == 1)
	{
		fd = open("/tmp/heredocfile", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	fd = macro_typered(fd);
	return (fd);
}

int	redirection(t_imp **imp)
{
	int	fd;
	int	tmp_fd_out;
	int	tmp_fd_in;
	int	i;

	fd = 0;
	tmp_fd_out = dup(1);
	tmp_fd_in = dup(0);
	fd = type_redirection(fd, *imp);
	i = error_file(fd, tmp_fd_out, tmp_fd_in);
	if (i == 0)
		return (0);
	if (g_global->sig_ex == 1)
	{
		dup_red(tmp_fd_out, tmp_fd_in);
		g_global->sig_ex = 0;
		return (1);
	}
	if (g_global->lst->cmd)
		ex_with_redriction(imp);
	close(fd);
	dup_red(tmp_fd_out, tmp_fd_in);
	return (1);
}
