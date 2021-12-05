#include "../minishell.h"

int    ft_cd(t_imp **imp)
{
    t_imp *tmp;
	char *str;
	char buff[100];

    tmp = *imp;
	str = ft_strdup("");
   if (g_global->lst->options[1] == NULL)
   {
       while ((tmp != NULL) && ft_strcmp(tmp->key, "HOME"))
       {
           tmp = tmp->next;
       }
	   if (tmp ==  NULL)
		{
			ft_putstr_fd(": cd: HOME not set\n", 2);
			g_global->error = ft_strdup("1");
			return (0);
		}
		else
		{
       		if(chdir(tmp->value) == -1)
			{
				ft_error(tmp->value, ": No such file or directory", "1");
				return (0);
			}
			tmp = *imp;
			while (tmp && ft_strcmp(tmp->key, "PWD"))
				tmp = tmp->next;
			if (tmp != NULL)
			{
				str = tmp->value;
				tmp->value = ft_strdup(getcwd(buff, 100));
			}
			tmp = *imp;
			while (tmp && ft_strcmp(tmp->key, "OLDPWD"))
				tmp = tmp->next;
			if (tmp != NULL)
				tmp->value = str;
			return (0);
		}
   }
   else if (chdir(g_global->lst->options[1]) == -1)
   {
	   ft_error(g_global->lst->options[1], ": No such file or directory", "1");
	   return (0);
   }
  	tmp = *imp;
	while (tmp && ft_strcmp(tmp->key, "PWD"))
		tmp = tmp->next;
	if (tmp != NULL)
	{
		str = tmp->value;
		tmp->value = ft_strdup(getcwd(buff, 100));
	}
	tmp = *imp;
	while (tmp && ft_strcmp(tmp->key, "OLDPWD"))
		tmp = tmp->next;
	if (tmp != NULL)
		tmp->value = str;
   return (0);

}