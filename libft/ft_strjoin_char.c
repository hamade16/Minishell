/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:51:27 by houbeid           #+#    #+#             */
/*   Updated: 2021/11/14 13:53:31 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char const *s1, char const *s2, char c)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1)
		return (0);
	str = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = c;
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
