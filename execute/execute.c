#include "../minishell.h"


struct imp	*gere_exp(char **envp)
{	struct imp *imp;
	struct imp *tmp;
	int i;
	int len;

	i = 0;
	len = 0;
	imp = malloc(sizeof(struct imp));
	tmp = imp;
	while (envp[i])
	{

		tmp->next = malloc(sizeof(struct imp));
		if (ft_strchr(envp[i], '='))
		{
			len = ft_strchr(envp[i], '=') - envp[i];
			tmp->key = ft_substr(envp[i], 0, len);
			tmp->value = ft_substr(envp[i], len + 1, ft_strlen(envp[i]));
			tmp->egale = 1;
		}
		else 
		{
			tmp->key = envp[i];
			tmp->value = NULL;
			tmp->egale = 0;
		}
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (imp);
}

void print_export(struct imp **imp)
{
	struct imp *tmp;

	tmp = *imp;
	while (tmp->next != NULL)
	{
		if(tmp->value != NULL)
		{
			printf ("declare -x ");
			printf("%s", tmp->key);
			printf ("=\"");
			printf("%s", tmp->value);
			printf("\"\n");
		}
		else
		{
			printf ("declare -x ");
			printf("%s", tmp->key);
		}
		tmp = tmp->next;
	}
}

struct imp *init_options()
{
	struct imp *init;
	struct imp *tmp;
	int len;
	int i;

	i = 0;
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

struct imp *manages_options(struct imp **imp)
{
	struct imp *tmp;
	struct imp	*init;
	struct imp	*tmp1;
	int i;

	init = init_options();
	tmp1 = init;
	tmp = imp;
	i = 0;
	while (tmp1->next != NULL)
	{
		while (tmp->next != NULL)
		{
			if (!ft_strcmp(tmp->key, tmp1->key))
			{
				
			}
		}
	}
}

void	execute(struct imp **imp)
{

	if (!ft_strcmp(g_cmds->cmd, "export"))
	{
		manages_options(imp);
		print_export(imp);
	}
}