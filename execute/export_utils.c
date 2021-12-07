/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:01:47 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 03:59:18 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	macro_print(char *str1, char *str2, int cmpt)
{
	int	i;

	i = 0;
	if (str1 != NULL)
	{
		printf ("declare -x ");
		printf("%s", str2);
		printf ("=\"");
		if ((cmpt % 2) == 0)
		{
			while (str1[i])
			{
				if (str1[i] != '\"')
					printf("%c", str1[i]);
				i++;
			}
		}
		printf("\"\n");
	}
	else
	{
		printf ("declare -x ");
		printf("%s", str2);
		printf("\n");
	}
}

void	remplir_imp(t_imp **imp, t_imp *tmp1)
{
	t_imp	*t;
	t_imp	*new;

	t = *imp;
	while (t->next)
		t = t->next;
	new = pmalloc(sizeof(t_imp));
	new->key = tmp1->key;
	new->value = tmp1->value;
	if (tmp1->egale == 1)
		new->egale = 1;
	else
		new->egale = 0;
	new->next = NULL;
	t->next = new;
}

void	var_exist(t_imp **tmp, t_imp *tmp1)
{
	(*tmp)->key = tmp1->key;
	(*tmp)->value = tmp1->value;
	(*tmp)->egale = 1;
}

void	imp_env(t_imp **tmp, char **envp, int i)
{
	int	len;

	if (ft_strchr(envp[i], '='))
	{
		len = ft_strchr(envp[i], '=') - envp[i];
		(*tmp)->key = ft_substr(envp[i], 0, len);
		(*tmp)->value = ft_substr(envp[i], len + 1, ft_strlen(envp[i]));
		(*tmp)->egale = 1;
	}
	else
	{
		(*tmp)->key = envp[i];
		(*tmp)->value = NULL;
		(*tmp)->egale = 0;
	}
}
