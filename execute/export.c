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
			// printf("==> %s\n", tmp->key);
			tmp->value = ft_substr(envp[i], len + 1, ft_strlen(envp[i]));
			tmp->egale = 1;
		}
		else 
		{
			tmp->key = envp[i];
			// printf("==> %s\n", tmp->key);
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