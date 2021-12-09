/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:12:34 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 14:12:36 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_splitted_wq(char *s, char c, size_t i)
{
	size_t	len;
	int		quote;

	len = 0;
	quote = 0;
	while (++i < ft_strlen(s))
	{
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'' && quote == 0)
				quote = 1;
			else if (s[i] == '"' && quote == 0)
				quote = 2;
			else if (s[i] == '\'' == quote == 1)
				quote = 0;
			else if (s[i] == '"' && quote == 2)
				quote = 0;
			i++;
		}
		if (s[i - 1] != c && quote == 0)
			len++;
	}
	return (len);
}

char	*ft_charjoin(char const *s, char const c)
{
	size_t	i;
	size_t	len_s;
	char	*new_string;

	if (!s)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	new_string = (char *)pmalloc(len_s + 2);
	ft_strcpy(new_string, s);
	new_string[len_s] = c;
	new_string[len_s + 1] = '\0';
	return (new_string);
}

void	ft_norm_split(char **str, char *s, size_t *i)
{
	char	*tmp;

	tmp = *str;
	*str = ft_charjoin(*str, s[(*i)++]);
	free(tmp);
}

char	**ft_split_wq(char *s, char c, size_t i, size_t j)
{
	size_t	len;
	char	**result;

	len = count_splitted_wq(s, c, -1);
	result = (char **)pmalloc(sizeof(char *) * (len + 1));
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && j < len)
	{
		if (s[i] && (s[i] != c || check_quotes_ind(s, i) != 0))
		{
			result[j] = ft_strdup_wrap("");
			while (s[i] && (s[i] != c || check_quotes_ind(s, i) != 0))
				ft_norm_split(&result[j], s, &i);
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}
