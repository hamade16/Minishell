#include "../minishell.h"

void    impecho()
{
    int i;
    int j;

    i = 1;
	if (!g_cmds->options[i])
		printf("\n");
	while (g_cmds->options[i])
	{	j = 0;
		if (g_cmds->options[i][j] == '-' && g_cmds->options[i][j + 1] == 'n')
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
		}
	}
	j = 0;
	if (g_cmds->options[1])
	{
		if (g_cmds->options[1][j] == '-')
		{
			j++;
			while (g_cmds->options[1][j])
			{
				if (g_cmds->options[1][j] != 'n')
				{
					printf("\n");
					break;
				}
				j++;
			}
		}
		else 
			printf("\n");
	}

}