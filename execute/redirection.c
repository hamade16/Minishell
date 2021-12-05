#include "../minishell.h"

void	dup_red(int a, int b)
{
	dup2(a, STDOUT_FILENO);
	dup2(b, STDIN_FILENO);
}

void	ex_with_redriction(struct imp **imp)
{
	if (!ft_strcmp(g_global->lst->cmd, "export") && g_global->lst->options && g_global->lst->options[1] != NULL)
		imp = manages_options(imp);
	if (!ft_strcmp(g_global->lst->cmd, "cd"))
		ft_cd(imp);
	if (!ft_strcmp(g_global->lst->cmd, "unset"))
		ft_unset(imp);
	if(!ft_strcmp(g_global->lst->cmd, "exit"))
		ft_exit();
	else
		ex_in_childs(imp);
}

int	type_redirection(int fd)
{
	int pid;
	int heredoc ;
	t_mini_cmd *c = g_global->lst->mini_cmd;

	heredoc = 0;
	pid = 0;
	while(c)
	{
		if (c->redir == 4)
		{
			heredoc = 1;
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
	while (g_global->lst->mini_cmd != NULL)
	{
		if (g_global->lst->mini_cmd->redir == 1)
    	{
			fd = red_out();
			if (fd == 0)
				return(0);
    	}
   		if (g_global->lst->mini_cmd->redir == 2)
    	{
			fd = red_in();
			if (fd == 0)
				return (0);
    	}
		if (g_global->lst->mini_cmd->redir == 3)
		{
			fd = open(g_global->lst->mini_cmd->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    		dup2(fd, STDOUT_FILENO);
    		close(fd);
		}
		if (g_global->lst->mini_cmd->next_mini != NULL)
		 	g_global->lst->mini_cmd = g_global->lst->mini_cmd->next_mini;
		else 
			break;
	}
	return (fd);
}

int	redirection(struct imp **imp)
{
	int fd;
	int tmp_fd_out;
	int tmp_fd_in;

	fd = 0;
	tmp_fd_out = dup(1);
    tmp_fd_in  = dup(0);
	fd = type_redirection(fd);
	if (fd < 0)
	{
		dup2(tmp_fd_out, STDOUT_FILENO);
		ft_error(g_global->lst->mini_cmd->filename,
			": No such file or directory", "1");
		return (0);
	}
	if (fd == 0)
	{
		dup_red(tmp_fd_out, tmp_fd_in);
		return(0);
	}
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
