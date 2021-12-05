/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:40:20 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/04 22:07:00 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

struct imp **ft_unset(struct imp **imp)
{
    struct imp *tmp;
    int i;
    struct imp *prev;

    i = 1;
    if(g_global->lst->options[1] == NULL)
        return (imp);
    while (g_global->lst->options[i])
    {
        //tmp = *imp;
        if (!(ft_strcmp((*imp)->key, g_global->lst->options[i])))
        {
            tmp = *imp;
            (*imp) = (*imp)->next;
            free(tmp);
        }
        else 
        {
            tmp = *imp;
            while (tmp != NULL && ft_strcmp(tmp->key, g_global->lst->options[i]))
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