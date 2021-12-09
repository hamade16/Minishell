/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extract_utils_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:37:00 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/08 21:37:02 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}
