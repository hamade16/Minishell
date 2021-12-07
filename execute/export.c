/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 01:43:28 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 21:58:20 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_caractere(char *str)
{
	if (str[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(str[0], 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export", 2);
		ft_putstr_fd(" [name[=value] ...] or export -p\n", 2);
		return (1);
	}
	return (0);
}

t_imp	*gere_exp(char **envp)
{	
	t_imp	*imp;
	t_imp	*tmp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	imp = pmalloc(sizeof(t_imp));
	tmp = imp;
	while (envp[i + 1])
	{
		tmp->next = pmalloc(sizeof(t_imp));
		imp_env(&tmp, envp, i);
		if (envp[i + 1])
			tmp = tmp->next;
		i++;
	}
	imp_env(&tmp, envp, i);
	tmp->next = NULL;
	return (imp);
}

void	f(t_imp **tmp1, t_imp **imp, int tm)
{
	int	i;

	i = 0;
	while ((*tmp1)->key[i])
	{
		if (((*tmp1)->key[i] != '_'
				&& !ft_isalnum((*tmp1)->key[i]))
			|| ((*tmp1)->key[0] != '_'
				&& !ft_isalpha((*tmp1)->key[0])))
		{
			ft_error((*tmp1)->key, "\' : not a valid identifier\n", "1");
			tm = 1;
			break ;
		}
		i++;
	}
	if (tm == 0)
		remplir_imp(imp, (*tmp1));
}

t_imp	**manages_options(t_imp **imp)
{
	t_imp	*tmp;
	t_imp	*init;
	t_imp	*tmp1;

	init = init_options();
	tmp1 = init;
	if (first_caractere(tmp1->key))
	{
		free_list(init);
		return (imp);
	}
	while (tmp1 != NULL)
	{
		tmp = *imp;
		while (tmp != NULL && ft_strcmp(tmp1->key, tmp->key))
			tmp = tmp->next;
		if (tmp == NULL)
			f(&tmp1, imp, 0);
		else
		{
			if (tmp1->egale == 1)
				var_exist(&tmp, tmp1);
		}
		if (tmp1->next == NULL)
			break ;
		tmp1 = tmp1->next;
	}
	free_list(init);
	return (imp);
}

void	print_export(t_imp **imp)
{
	t_imp	*tmp;
	int		i;
	int		cmpt;

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
		macro_print(tmp->value, tmp->key, cmpt);
		tmp = tmp->next;
	}
}
