/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:38:36 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/05 16:39:01 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_get_env_size(t_imp *env_lst)
{
	size_t	len;

	len = 0;
	while (env_lst)
	{
		env_lst = env_lst->next;
		len++;
	}
	return (len);
}

char	**ft_convert_to_arr(t_imp *env_lst)
{
	char	**env_arr;
	size_t	len;
	size_t	len2;
	size_t	i;
	size_t	j;

	i = 0;
	len = ft_get_env_size(env_lst);
	env_arr = pmalloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		j = 0;
		if (env_lst->value)
			len2 = ft_strlen(env_lst->value);
		else
			len2 = 0;
		env_arr[i] = pmalloc(sizeof(char)
				* (ft_strlen(env_lst->key)
					+ len2 + 1 + 1));
		env_arr[i][j] = 0;
		ft_strlcat(env_arr[i], env_lst->key, ft_strlen(env_lst->key) + 1);
		ft_strlcat(env_arr[i], "=", ft_strlen(env_lst->key) + 1 + 1);
		if (len2)
			ft_strlcat(env_arr[i], env_lst->value,
				ft_strlen(env_lst->key) + len2 + 1 + 1);
		env_lst = env_lst->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
