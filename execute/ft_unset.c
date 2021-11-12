#include "../minishell.h"

void  ft_unset(struct imp **imp)
{
    struct imp *tmp;
    int i;
    struct imp *tmp1;
    struct imp *prev;

    i = 0;
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
            while (tmp->next != NULL && ft_strcmp(tmp->key, g_cmds->options[i]))
            {
                prev = tmp;
                tmp = tmp->next;
            }
            if (tmp->next != NULL)
            {
                prev->next = tmp->next;
                free(tmp);
            }
        }
    }

}