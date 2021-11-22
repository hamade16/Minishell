#include "../minishell.h"

void    ft_cd(struct  imp **imp)
{
    //printf("%s", imp->key);
    struct imp *tmp;

    tmp = *imp;
   if (g_cmds->options[1] == NULL)
   {
       while ((tmp != NULL) && ft_strcmp(tmp->key, "HOME"))
       {
           tmp = tmp->next;
       }
	   if (tmp ==  NULL)
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 1);
		}
		else
       		chdir(tmp->value);
   }
   else if (chdir(g_cmds->options[1]) == -1)
   {
       ft_putstr_fd("bash: cd: ", 1);
       ft_putstr_fd(g_cmds->options[1], 1);
	   ft_putstr_fd(": ", 1);
       perror("");
   }
}