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

struct imp **manages_options(struct imp **imp)
{
	struct imp *tmp;
	struct imp	*init;
	struct imp	*tmp1;
	struct imp *tmp2;
	int 		i;
	struct imp *new;

	
	init = init_options();
	tmp1 = init;
	i = 0;

	while (tmp1->next != NULL)
	{ 
		tmp = *imp; 
		while (tmp != NULL && ft_strcmp(tmp1->key, tmp->key)){
			tmp = tmp->next;
			// printf("|%p| * |%s * %p|\n", tmp1->key, tmp->key, tmp->key);
		}
		if (tmp == NULL)
		{
			struct imp *t = *imp;
			while (t->next)
				t = t->next;
			new = malloc(sizeof(struct imp));
			new->key = tmp1->key;
			new->value = tmp1->value;
			if (tmp1->egale == 1)
				new->egale = 1;
			else
				new->egale = 0;
			new->next = NULL;
			t->next = new;
		}
		else
		{
			if (tmp1->egale == 1)
			{
				tmp->key = tmp1->key;
				tmp->value = tmp1->value;
				tmp->egale = 1;
			}
		}
		tmp1 = tmp1->next;
	}
	return (imp);
}

void	execute(struct imp **imp, char **envp)
{
	int fd;
	int pid;
	int tmp_fd;
	if (g_cmds->mini_cmd != NULL)
	{
		// pid = fork();
		// if (!pid)
		// {
				//fd = open(g_cmds->mini_cmd->filename, O_WRONLY | O_CREAT, 0644);
				//tmp_fd = dup(1);
				//dup2(fd, 1);

			//}
			/*if (g_cmds->mini_cmd->redir == 2)
			{
				//tmp_fd = dup(0);
				dup2(fd, 0);

			}*/
			if (g_cmds->mini_cmd->redir == 1)
    		{
				fd = open(g_cmds->mini_cmd->filename, O_WRONLY | O_CREAT, 0644);
        		tmp_fd = dup(1);
        		dup2(fd, STDOUT_FILENO);
       			//close(fd);
    		}
   			if (g_cmds->mini_cmd->redir == 2)
    		{
				 fd = open(g_cmds->mini_cmd->filename, O_RDONLY, 0);
    			tmp_fd  = dup(0);
   				 dup2(fd, STDIN_FILENO);
					printf ("\nhamade\n");
    			//in = 0;
    		}
		//printf("%d", g_cmds->is_builtin);
			if (!ft_strcmp(g_cmds->cmd, "export") && (g_cmds->options[1] == NULL))
					print_export(imp);
			if (!ft_strcmp(g_cmds->cmd, "cd"))
				ft_cd(imp);
			if (!ft_strcmp(g_cmds->cmd, "unset"))
				ft_unset(imp);
			if(!ft_strcmp(g_cmds->cmd, "exit"))
				ft_exit();
			// exit(0);
		// }
			else
				ex_in_childs(imp, envp);


		/*if (!ft_strcmp(g_cmds->cmd, "echo"))
			impecho();
		if (!ft_strcmp(g_cmds->cmd, "pwd"))
			ft_pwd();
		if(!ft_strcmp(g_cmds->cmd, "env"))
			print_env(imp);
		}
		else
			ft_execve(envp);*/
		dup2(tmp_fd, 1);
		//close(fd);
	}
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
				//printf("hamada");
		}
	}
}