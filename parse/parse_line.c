/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:38:00 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 17:38:03 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_append(char ***opt, char *newopt)
{
	size_t	i;
	size_t	len;
	char	**tmp;

	if (*opt == NULL)
	{
		*opt = pmalloc(sizeof(char *) * 2);
		(*opt)[0] = newopt;
		(*opt)[1] = NULL;
	}
	else
	{
		len = 0;
		while ((*opt)[len])
			len++;
		tmp = *opt;
		*opt = pmalloc(sizeof(char *) * (len + 1 + 1));
		i = -1;
		while (++i < len)
			(*opt)[i] = tmp[i];
		free(tmp);
		(*opt)[i] = newopt;
		(*opt)[i + 1] = NULL;
	}
}

void	handle_line(char *line, t_imp *env)
{
	if (line)
	{
		if (check_forbidden(line))
		{
			if (check_quotes(line))
			{
				if (check_redirections(line) && check_end_redirections(line))
				{
					ft_extract_it(&g_global->lst, line, 0);
					ft_expand_data(&g_global->lst, env);
					ft_unquote(&g_global->lst);
					g_global->error = "0";
				}
				else
				{
					g_global->error = "258";
					ft_putstr_fd("minishell: syntax error\n", 0);
				}
			}
		}
	}
}
