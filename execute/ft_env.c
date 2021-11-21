#include "../minishell.h"

void    print_env(struct imp **imp)
{
    struct imp *tmp;

	tmp = *imp;
	while (tmp != NULL)
	{
        if (tmp->egale == 1)
        {
		    if(tmp->value != NULL)
		    {
			    printf("%s", tmp->key);
                printf ("=");
			    printf("%s", tmp->value);
			    printf("\n");
		    }
		    else
		    {
			    printf("%s", tmp->key);
                printf ("=");
			    printf("\n");
		    }
        }
		tmp = tmp->next;
	}
}