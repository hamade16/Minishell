/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 21:07:35 by abel-haj          #+#    #+#             */
/*   Updated: 2021/11/12 19:42:00 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t			i;
// 	unsigned char	*f_string;
// 	unsigned char	*s_string;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (0);
// 	f_string = (unsigned char *)s1;
// 	s_string = (unsigned char *)s2;
// 	while (f_string[i] || s_string[i])
// 	{
// 		if (f_string[i] != s_string[i])
// 			return (f_string[i] - s_string[i]);
// 		i++;
// 	}
// 	return (0);
// }

int ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
