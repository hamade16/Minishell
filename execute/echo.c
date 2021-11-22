#include "../minishell.h"

void    impecho()
{
    int i;
    int j;

    i = 1;
	while (g_cmds->options[i])
	{	j = 0;
		if (g_cmds->options[i][j] == '-')
		{
			j++;
			while (g_cmds->options[i][j] && g_cmds->options[i][j] == 'n')
				j++;
			if (g_cmds->options[i][j])
			{
       			 while (g_cmds->options[i])
       		 	{
       		    	 printf("%s", g_cmds->options[i]);
       		     	if (g_cmds->options[i + 1])
       		        	 printf(" ");
       		     	i++;
       		 	}
				//printf("hamade\n");
				break;
			}
			else
			{
				i++;
			}
		}
		else
		{
			 while (g_cmds->options[i])
       		{
       		    printf("%s", g_cmds->options[i]);
       		    if (g_cmds->options[i + 1])
       		        printf(" ");
       		    i++;
       		}
			if (g_cmds->options[1][0] != '-')
				printf("\n");
		}
	}
    /*if (g_cmds->options[i][j] == '-')
    {
		j++;
        while (g_cmds->options[i][j] && g_cmds->options[i][j] == 'n')
            j++;
		if (g_cmds->options[i][j] != NULL)
		{
       		 while (g_cmds->options[i] != NULL)
       		 {
       		     printf("%s", g_cmds->options[i]);
       		     if (g_cmds->options[i + 1] != NULL)
       		         printf(" ");
       		     i++;
       		 }
		}
		else
			i++;
    }
    else
    {
        while (g_cmds->options[i] != NULL)
        {
            printf ("%s", g_cmds->options[i]);
            if (g_cmds->options[i + 1] != NULL)
                printf(" ");
            i++;
        }
        printf("\n");
    }*/

}