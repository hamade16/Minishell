#include "../minishell.h"

void    impecho(void)
{
    int i;
    int j;

    i = 1;
	if (!g_global->lst->options[i])
		printf("\n");
	while (g_global->lst->options[i])
	{	j = 0;
		if (g_global->lst->options[i][j] == '-' && g_global->lst->options[i][j + 1] == 'n')
		{
			j++;
			while (g_global->lst->options[i][j] && g_global->lst->options[i][j] == 'n')
				j++;
			if (g_global->lst->options[i][j])
			{
       			 while (g_global->lst->options[i])
       		 	{
       		    	printf("%s", g_global->lst->options[i]);
       		     	if (g_global->lst->options[i + 1])
       		        	 printf(" ");
       		     	i++;
       		 	}
				break;
			}
			else
			{
				i++;
			}
		}
		else
		{
			 while (g_global->lst->options[i])
       		{
       		    printf("%s", g_global->lst->options[i]);
       		    if (g_global->lst->options[i + 1])
       		        printf(" ");
       		    i++;
       		}
		}
	}
	j = 0;
	if (g_global->lst->options[1])
	{
		if (g_global->lst->options[1][j] == '-')
		{
			j++;
			while (g_global->lst->options[1][j])
			{
				if (g_global->lst->options[1][j] != 'n')
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