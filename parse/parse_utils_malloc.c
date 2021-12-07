/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_malloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:13:20 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:13:22 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*pmalloc(size_t size)
{
	void	*data;

	data = malloc(size);
	if (data)
		return (data);
	else
	{
		ft_putstr_fd("Cannot allocate memory\n", 0);
		exit(12);
	}
}

void	ft_exit_malloc(void)
{
	ft_putstr_fd("Cannot allocate memory\n", 0);
	exit(12);
}

char	*ft_substr_wrap(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_substr(s, start, len);
	if (str == NULL)
		ft_exit_malloc();
	return (str);
}

char	*ft_strdup_wrap(const char *s)
{
	char	*str;

	str = ft_strdup(s);
	if (str == NULL)
		ft_exit_malloc();
	return (str);
}
