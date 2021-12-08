/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:38:36 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 19:57:04 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_imp	**free_list_return(t_imp *init, t_imp **imp)
{
	t_imp	*tmp;

	while (init != NULL)
	{
		tmp = init;
		init = init->next;
		free(tmp->key);
		tmp->key = NULL;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
	return (imp);
}

static size_t	ft_get_env_size(t_imp *env_lst)
{
	size_t	len;

	len = 0;
	while (env_lst)
	{
		if (env_lst->egale == 1)
			len++;
		env_lst = env_lst->next;
	}
	return (len);
}

char	*ft_convert_norm(char *key, char *value, int len)
{
	char	*new;
	int		j;

	j = 0;
	new = pmalloc(sizeof(char)
			* (ft_strlen(key)
				+ len + 1 + 1));
	new[j] = 0;
	ft_strlcat(new, key, ft_strlen(key) + 1);
	ft_strlcat(new, "=", ft_strlen(key) + 1 + 1);
	if (len)
		ft_strlcat(new, value,
			ft_strlen(key) + len + 1 + 1);
	return (new);
}

char	**ft_convert_to_arr(t_imp *env_lst)
{
	char	**env_arr;
	size_t	len;
	size_t	len2;
	size_t	i;

	i = 0;
	len = ft_get_env_size(env_lst);
	env_arr = pmalloc(sizeof(char *) * (len + 1));
	while (env_lst && i < len)
	{
		if (env_lst->value)
			len2 = ft_strlen(env_lst->value);
		else
			len2 = 0;
		if (env_lst->egale == 1)
		{
			env_arr[i] = ft_convert_norm(env_lst->key, env_lst->value, len2);
			i++;
		}
		env_lst = env_lst->next;
	}
	env_arr[len] = NULL;
	return (env_arr);
}

void	free_double(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env[i]);
	}
	free(env);
	env = NULL;
}
