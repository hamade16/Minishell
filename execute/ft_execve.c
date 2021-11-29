#include "../minishell.h"

/*char	ft_free_first(char *first, char *str)
{
	if (first == 0)
		return (str);
	free(first);
	return (str);
}*/

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


char   *path_env(struct imp **imp)
{
    int i;

    i = 0;
	struct imp *tmp;

	tmp = *imp;
    while (tmp)
    {
		//printf("hamade\n");
        if (ft_strcmp(tmp->key, "PATH") == 0)
            break ;
        tmp = tmp->next;
    }
	//printf("hamade\n");
	if (tmp == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_global->lst->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(0);
		return (0);
	}
    return (tmp->value);
}

void	error_command(char	*str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(" : command not found\n", 2);

	
}

void	ft_perror(char *cmd)
{
	perror(cmd);
	exit(127);
}

char    *research_path(struct imp **imp)
{
    char	**path;
	char	*pathname;
	int		i;

	i = 0;
	if (!g_global->lst->cmd)
		error_command(NULL);
	if (access(g_global->lst->cmd, F_OK) == 0 && g_global->lst->cmd[0] == '/')
		return (ft_strdup(g_global->lst->cmd));
	path = ft_split(path_env(imp), ':');
	while (path[i])
	{
		pathname = ft_strjoin_char(path[i], g_global->lst->cmd, '/');
		if (access(pathname, F_OK) == 0)
			break ;
		i++;
		free(pathname);
		/*if (path[i] == 0)
			error_command(g_global->lst->cmd);*/
	}
	if (path[i] == NULL)
		return (NULL);
	ft_free_split(path);
	return (pathname);

}

int    ft_execve(struct imp **imp, char **envp)
{
    char *pathname;
    int pid;

    // printf("%s\n", pathname);
	if (access((g_global->lst->cmd), F_OK) == 0)
	{
		if (access((g_global->lst->cmd),X_OK) == 0)
		{
			//printf ("***hamade***\n");
			pid = fork();
    		wait(0);
			if (pid == 0)
			{
				execve(g_global->lst->cmd, g_global->lst->options, envp);
				exit(0);

			}
		}
		else
		{
    		
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(g_global->lst->cmd, 2);
			ft_putstr_fd(": Permission denied\n", 1);
			g_global->error = ft_strdup("126");
			return (0);
		}
	/*if (pathname == NULL)
		exit (0);*/
    //    if child
    		/*if (pid == 0)
			{
    		    execve(pathname, g_global->lst->options, envp);
				exit(0);

			}
		}*/
	}
	else 
	{
    	pathname = research_path(imp);
		if ((pathname == NULL) && ft_strchr(g_global->lst->cmd, '/'))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(g_global->lst->cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_global->error = ft_strdup("127");
			return (0);
		}
		if (pathname == NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(g_global->lst->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			g_global->error = ft_strdup("127");
			return (0);
		}
		/*if (g_global->lst->options[1])
		{
			if 
		}*/
		/*if (g_global->lst->options[1])
		{
			if (access((g_global->lst->options[1]), F_OK) != 0)
			{
				ft_putstr_fd(g_global->lst->cmd, 1);
				ft_putstr_fd(": ", 1);
				ft_putstr_fd(g_global->lst->options[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
				g_global->error = ft_strdup("1");
				return (0);
			}
		}*/
    //    if child
		pid = fork();
    	wait(0);
    	if (pid == 0)
		{
    	   if (execve(pathname, g_global->lst->options, envp) == -1)
				g_global->error = ft_strdup("1");

			exit(0);
		}
		/*printf("lwalida\n");
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_global->lst->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_global->error = ft_strdup("127");*/
	}
	return (0);
}