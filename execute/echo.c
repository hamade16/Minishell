#include "../minishell.h"

void    impecho()
{
    int i;
    int j;

    i = 1;
    j = 1;
    if (!ft_strcmp(g_cmds->options[i], "-n"))
    {
        while (!ft_strcmp(g_cmds->options[i], "-n"))
            i++;
        while (g_cmds->options[i] != NULL)
        {
            printf("%s", g_cmds->options[i]);
            if (g_cmds->options[i + 1] != NULL)
                printf(" ");
            i++;
        }
    }
    else
    {
        while (g_cmds->options[i] != NULL)
        {
            printf ("%s", g_cmds->options[i]);
            if (g_cmds->options[i +1] != NULL)
                printf(" ");
            i++;
        }
        printf("\n");
    }

}