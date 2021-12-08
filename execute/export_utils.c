/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:01:47 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 22:14:08 by houbeid          ###   ########.fr       */
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
	new->key = ft_strdup_wrap(tmp1->key);
	if (tmp1->value)
		new->value = ft_strdup_wrap(tmp1->value);
	else
		new->value = ft_strdup_wrap("");
	if (tmp1->egale == 1)
		new->egale = 1;
	else
		new->egale = 0;
	new->next = NULL;
	t->next = new;
}

void	var_exist(t_imp **tmp, t_imp *tmp1)
{
	char	*imp;
	char	*imp1;

	imp = (*tmp)->key;
	(*tmp)->key = ft_strdup_wrap(tmp1->key);
	free(imp);
	imp = NULL;
	imp1 = (*tmp)->value;
	(*tmp)->value = ft_strdup_wrap(tmp1->value);
	free(imp1);
	imp1 = NULL;
	(*tmp)->egale = 1;
}

void	imp_env(t_imp **tmp, char **envp, int i)
{
	int	len;

	if (ft_strchr(envp[i], '='))
	{
		len = ft_strchr(envp[i], '=') - envp[i];
		(*tmp)->key = ft_substr_wrap(envp[i], 0, len);
		(*tmp)->value = ft_substr_wrap(envp[i], len + 1, ft_strlen(envp[i]));
		(*tmp)->egale = 1;
	}
	else
	{
		(*tmp)->key = envp[i];
		(*tmp)->value = NULL;
		(*tmp)->egale = 0;
	}
}
