#include "../minishell.h"

struct imp *init_options()
{
	struct imp *init;
	struct imp *tmp;
	int len;
	int i;
	char *opt;

	i = 1;
	len = 0;
	init = malloc(sizeof(struct imp));
	tmp = init;
	while (g_global->lst->options[i])
	{

		tmp->next = malloc(sizeof(struct imp));
		opt = ft_strchr(g_global->lst->options[i], '=');
		if (opt)
		{
			len = opt - g_global->lst->options[i];
			tmp->key = ft_substr(g_global->lst->options[i], 0, len);
			if (opt[1] == '"' || opt[1] == '\'')
				tmp->value = ft_substr(g_global->lst->options[i], len + 1 + 1, ft_strlen(opt) - 1 - 2);
			else
				tmp->value = ft_substr(g_global->lst->options[i], len + 1, ft_strlen(g_global->lst->options[i]));

			tmp->egale = 1;
		}
		else
		{
			tmp->key = g_global->lst->options[i];
			tmp->value = NULL;
			tmp->egale = 0;
		}
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (init);
}

int	type_redirection(int fd)
{
	int heredoc = 0;
	t_mini_cmd *c = g_global->lst->mini_cmd;

	while(c)
	{
		if (c->redir == 4)
		{
			heredoc = 1;
			fd = open("/tmp/heredocfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				char *line;
				line = readline("> ");
				//printf("|%s| |%s|\n", line, c->filename);
				if (ft_strcmp(line, c->filename))
					ft_putendl_fd(line, fd);
				else
					break;
			}
			c = c->next_mini;
			close(fd);
		}
		else
			c = c->next_mini;
	}
	if (heredoc == 1)
	{
		fd = open("/tmp/heredocfile", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		//heredoc = 0;
	}
	while (g_global->lst->mini_cmd != NULL)
	{
		if (g_global->lst->mini_cmd->redir == 1)
    	{
			fd = open(g_global->lst->mini_cmd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    		dup2(fd, STDOUT_FILENO);
    		close(fd);
    	}
   		if (g_global->lst->mini_cmd->redir == 2)
    	{
			//printf("********%s\n", g_global->lst->mini_cmd->filename);
			 fd = open(g_global->lst->mini_cmd->filename, O_RDONLY);
			if (fd < 0)
				return (fd);
   			dup2(fd, STDIN_FILENO);
			close(fd);
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

int	redirection(struct imp **imp, char **envp)
{
	int fd;
	int tmp_fd_out;
	int tmp_fd_in;

	tmp_fd_out = dup(1);
    tmp_fd_in  = dup(0);
	fd = type_redirection(fd);
	if (fd < 0)
	{
		dup2(tmp_fd_out, STDOUT_FILENO);
		ft_putstr_fd("minishell:  ", 2);
		ft_putstr_fd(g_global->lst->mini_cmd->filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		//dup2(tmp_fd_in, STDIN_FILENO);
		return (0);
	}
	if (!ft_strcmp(g_global->lst->cmd, "export") && (g_global->lst->options[1] != NULL))
		imp = manages_options(imp);
	if (!ft_strcmp(g_global->lst->cmd, "cd"))
		ft_cd(imp);
	if (!ft_strcmp(g_global->lst->cmd, "unset"))
		ft_unset(imp);
	if(!ft_strcmp(g_global->lst->cmd, "exit"))
		ft_exit();
	else
		ex_in_childs(imp, envp);
	close(fd);
	dup2(tmp_fd_out, STDOUT_FILENO);
	dup2(tmp_fd_in, STDIN_FILENO);
	return (1);
}

void	execute(struct imp **imp, char **envp)
{
	int i;

	if (!ft_strcmp(g_global->error, "0"))
	{
		if (g_global->lst->mini_cmd != NULL)
			i = redirection(imp, envp);
		else
		{
			if (g_global->lst->is_builtin)
			{
				if (!ft_strcmp(g_global->lst->cmd, "export"))
				{
					if (g_global->lst->options[1] != NULL)
						imp = manages_options(imp);
					else
						print_export(imp);
				}
				if (!ft_strcmp(g_global->lst->cmd, "echo"))
						impecho();
				if (!ft_strcmp(g_global->lst->cmd, "unset"))
						ft_unset(imp);
				if (!ft_strcmp(g_global->lst->cmd, "cd"))
						ft_cd(imp);
				if (!ft_strcmp(g_global->lst->cmd, "pwd"))
						ft_pwd();
				if(!ft_strcmp(g_global->lst->cmd, "exit"))
						ft_exit();
				if(!ft_strcmp(g_global->lst->cmd, "env"))
						print_env(imp);
			}
			else
			{
				ft_execve(imp, envp);
			}
		}
	}
}