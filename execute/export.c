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
		if (envp[i + 1])
			tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;

	return (imp);
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

void print_export(struct imp **imp)
{
	struct imp *tmp;

	tmp = *imp;
	while (tmp != NULL)
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
			printf("\n");
		}
		tmp = tmp->next;
	}
}