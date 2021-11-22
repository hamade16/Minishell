#include "../minishell.h"

struct imp *init_options()
{
	struct imp *init;
	struct imp *tmp;
	int len;
	int i;

	i = 1;
	len = 0;
	init = malloc(sizeof(struct imp));
	tmp = init;
	while (g_cmds->options[i])
	{

		tmp->next = malloc(sizeof(struct imp));
		if (ft_strchr(g_cmds->options[i], '='))
		{
			len = ft_strchr(g_cmds->options[i], '=') - g_cmds->options[i];
			tmp->key = ft_substr(g_cmds->options[i], 0, len);
			tmp->value = ft_substr(g_cmds->options[i], len + 1, ft_strlen(g_cmds->options[i]));
			tmp->egale = 1;
		}
		else
		{
			tmp->key = g_cmds->options[i];
			tmp->value = NULL;
			tmp->egale = 0;
		}
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (init);
}

void	type_redirection(int fd)
{
	while (g_cmds->mini_cmd != NULL)
	{
		if (g_cmds->mini_cmd->redir == 1)
    	{
			fd = open(g_cmds->mini_cmd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    		dup2(fd, STDOUT_FILENO);
    		close(fd);
    	}
   		if (g_cmds->mini_cmd->redir == 2)
    	{
			printf("********%s\n", g_cmds->mini_cmd->filename);
			 fd = open(g_cmds->mini_cmd->filename, O_RDONLY);
			 if (fd < 0)
			 {
			 	perror("g_cmds->mini_cmd->filename :") ;
				break;
			 }
   			 dup2(fd, STDIN_FILENO);
    	}
		if (g_cmds->mini_cmd->redir == 3)
		{
			fd = open(g_cmds->mini_cmd->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    		dup2(fd, STDOUT_FILENO);
    		close(fd);
		}
		if (g_cmds->mini_cmd->next_mini != NULL)
			g_cmds->mini_cmd = g_cmds->mini_cmd->next_mini;
		else 
			break;
	}
}

void	redirection(struct imp **imp, char **envp)
{
	int fd;
	int tmp_fd_out;
	int tmp_fd_in;

	tmp_fd_out = dup(1);
    tmp_fd_in  = dup(0);
	type_redirection(fd);
	if (!ft_strcmp(g_cmds->cmd, "export") && (g_cmds->options[1] != NULL))
		imp = manages_options(imp);
	if (!ft_strcmp(g_cmds->cmd, "cd"))
		ft_cd(imp);
	if (!ft_strcmp(g_cmds->cmd, "unset"))
		ft_unset(imp);
	if(!ft_strcmp(g_cmds->cmd, "exit"))
		ft_exit();
	else
		ex_in_childs(imp, envp);
	close(fd);
	dup2(tmp_fd_out, STDOUT_FILENO);
	dup2(tmp_fd_in, STDIN_FILENO);
}

void	execute(struct imp **imp, char **envp)
{
	if (g_cmds->mini_cmd != NULL)
		redirection(imp, envp);
	else
	{
		 if (g_cmds->is_builtin)
        {
            if (!ft_strcmp(g_cmds->cmd, "export"))
            {
                if (g_cmds->options[1] != NULL)
                    imp = manages_options(imp);
                else
                    print_export(imp);
            }
            if (!ft_strcmp(g_cmds->cmd, "echo"))
                    impecho();
            if (!ft_strcmp(g_cmds->cmd, "unset"))
                    ft_unset(imp);
            if (!ft_strcmp(g_cmds->cmd, "cd"))
                    ft_cd(imp);
            if (!ft_strcmp(g_cmds->cmd, "pwd"))
                    ft_pwd();
            if(!ft_strcmp(g_cmds->cmd, "exit"))
                    ft_exit();
            if(!ft_strcmp(g_cmds->cmd, "env"))
                    print_env(imp);
        }
        else
		{
            ft_execve(envp);
		}
	}
}