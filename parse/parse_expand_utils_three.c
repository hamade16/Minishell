/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_utils_three.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:14:03 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:14:05 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_norm(char *str, t_imp *env)
{
	char	*tmp;

	tmp = str;
	str = expand_it(str, env, 0);
	free(tmp);
	return (str);
}

int	ft_count_words(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 1;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			len++;
		}
		i++;
	}
	return (len);
}

size_t	get_opt_size(void)
{
	size_t	i;

	i = 0;
	if (g_global->lst->options)
	{
		while (g_global->lst->options[i])
			i++;
	}
	return (i);
}

char	**ft_expand_cmd_new(char **parts, char *new, size_t i, size_t j)
{
	char	**new_opt;

	new_opt = pmalloc(sizeof(char *) * (ft_count_words(new) + get_opt_size()));
	while (parts[++i])
		new_opt[i] = ft_strdup_wrap(parts[i]);
	if (g_global->lst->options)
	{
		while (g_global->lst->options[j])
		{
			new_opt[i] = ft_strdup_wrap(g_global->lst->options[j]);
			i++;
			j++;
		}
		j = 0;
		while (g_global->lst->options[j])
		{
			free(g_global->lst->options[j]);
			j++;
		}
		free(g_global->lst->options);
	}
	new_opt[i] = NULL;
	return (new_opt);
}

char	*ft_expand_cmd(char *str, t_imp *env)
{
	char	*new;
	char	*result;
	char	**parts;
	size_t	i;

	new = ft_expand_norm(str, env);
	if (ft_count_words(new) > 0)
	{
		parts = ft_split_wq(new, ' ', 0, 0);
		result = ft_strdup_wrap(parts[0]);
		if (parts[1] != NULL)
			g_global->lst->options = ft_expand_cmd_new(parts, new, -1, 1);
		i = 0;
		while (parts[i])
		{
			free(parts[i]);
			i++;
		}
		free(parts);
		free(new);
	}
	else
		result = new;
	return (result);
}
