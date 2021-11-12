#include "../minishell.h"

struct imp *init_options()
{
	struct imp *init;
	struct imp *tmp;
	int len;
	int i;

	i = 0;
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
		while (tmp->next != NULL && ft_strcmp(tmp1->key, tmp->key))
			tmp = tmp->next;
		if (tmp->next == NULL)
		{
			new = malloc(sizeof(struct imp));
			new->key = tmp1->key;
			new->value = tmp1->value;
			new->next = NULL;
			tmp = new;
			//tmp = tmp->next;
			printf("tmp->key = %s\n", tmp->key);
			/*tmp->next = malloc(sizeof(struct imp));
			//printf ("hamade\n");
			tmp = tmp->next;
			tmp->key = tmp1->key;
			tmp->value = tmp1->value;
			tmp->next = NULL;*/
		}
		else
		{
			if (tmp1->egale == 1)
			{
				tmp->key = tmp1->key;
				tmp->value = tmp1->value;
			}
		}
		tmp1 = tmp1->next;
	}
	//print_export(imp);
	 tmp2 = *imp;
	 while (tmp2->next != NULL)
	 {
	 	printf("%s\n", tmp2->key);
	 	tmp2 = tmp2->next;
	 }
	return (imp);
}

void	execute(struct imp **imp)
{

	char *buff;

	if (!ft_strcmp(g_cmds->cmd, "export"))
	{
		if (g_cmds->options != NULL)
			imp = manages_options(imp);
		// print_export(imp);
	}
	if (!ft_strcmp(g_cmds->cmd, "cd"))
	{
		chdir(g_cmds->options[0]);
		printf("%s\n", getcwd(buff, 100));
	}
	if (!ft_strcmp(g_cmds->cmd, "echo"))
		impecho();
}