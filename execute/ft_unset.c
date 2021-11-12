/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:44:08 by houbeid           #+#    #+#             */
/*   Updated: 2021/11/12 14:55:18 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct imp  ft_unset(struct imp **imp)
{
    struct imp *tmp;

    tmp = *imp;
    while (tmp->next != NULL)
    {
        if (!ft_strcmp(tmp->key, g_cmds->options[0]))
        {
            if ((*imp)->key == g_cmds->options[0])
        }
    }
}