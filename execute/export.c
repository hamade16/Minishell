#include "../minishell.h"


t_imp	*gere_exp(char **envp)
{	t_imp *imp;
	t_imp *tmp;
	int i;
	int len;

	i = 0;
	len = 0;
	imp = malloc(sizeof(t_imp));
	tmp = imp;
	while (envp[i])
	{

		tmp->next = malloc(sizeof(t_imp));
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

t_imp **manages_options(t_imp **imp)
{
	t_imp *tmp;
	t_imp	*init;
	t_imp	*tmp1;
	int 		i;
	t_imp *new;
	int tm;

	
	init = init_options();
	tmp1 = init;
	if (tmp1->key[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(tmp1->key[0], 2);
		ft_putchar_fd(tmp1->key[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export [-nf] [name[=value] ...] or export -p\n", 2);
		return(imp);
	}
	while (tmp1->next != NULL)
	{ 
		tm = 0;
		tmp = *imp; 
		while (tmp != NULL && ft_strcmp(tmp1->key, tmp->key)){
			tmp = tmp->next;
		}
		if (tmp == NULL)
		{
			i = 0;
			while (tmp1->key[i])
			{
				if ((tmp1->key[i] != '_' && !ft_isalnum(tmp1->key[i])) || (tmp1->key[0] != '_' && !ft_isalpha(tmp1->key[0])))
				{
					ft_putstr_fd("minishell: export: `", 2);
					ft_putstr_fd(tmp1->key, 2);
					ft_putstr_fd("\' : not a valid identifier\n", 2);
					g_global->error = "1";
					tm = 1;
					break;
				}
				i++;
			}
			if (tm == 0)
			{
				t_imp *t = *imp;
				while (t->next)
					t = t->next;
				new = malloc(sizeof(t_imp));
				new->key = tmp1->key;
				new->value = tmp1->value;
				if (tmp1->egale == 1)
					new->egale = 1;
				else
					new->egale = 0;
				new->next = NULL;
				t->next = new;
			}
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

void print_export(t_imp **imp)
{
	t_imp *tmp;
	int i;
	int cmpt;

	i = 0;
	cmpt = 0;
	tmp = *imp;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->value != NULL)
		{
			while (tmp->value[i])
			{
				if (tmp->value[i] == '\"')
					cmpt++;
				i++;
			}
		}
		i = 0;
		if(tmp->value != NULL)
		{
			printf ("declare -x ");
			printf("%s", tmp->key);
			printf ("=\"");
			if ((cmpt % 2) == 0)
			{
				while (tmp->value[i])
				{
					if (tmp->value[i] != '\"')
						printf("%c", tmp->value[i]);
					i++;
				}
			}
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