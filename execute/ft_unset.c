/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:40:20 by houbeid           #+#    #+#             */
/*   Updated: 2021/11/14 15:34:35 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

struct imp **ft_unset(struct imp **imp)
{
    struct imp *tmp;
    int i;
    struct imp *tmp1;
    struct imp *prev;

    i = 1;
    if(g_cmds->options[1] == NULL)
        return (imp);
    while (g_cmds->options[i])
    {
        //tmp = *imp;
        if (!(ft_strcmp((*imp)->key, g_cmds->options[i])))
        {
            tmp = *imp;
            (*imp) = (*imp)->next;
            free(tmp);
        }
        else 
        {
            tmp = *imp;
            while (tmp != NULL && ft_strcmp(tmp->key, g_cmds->options[i]))
            {
                prev = tmp;
                tmp = tmp->next;
            }
            if (tmp != NULL)
            {
                prev->next = tmp->next;
                free(tmp);
            }
        }
        i++;
    }
    return (imp);
}