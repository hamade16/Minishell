#include "../minishell.h"

struct imp *init_options()
{
	struct imp *init;
	struct imp *tmp;
	int len;
	int i;
	char *opt;

	i = 1;
	len = 0;
	init = malloc(sizeof(struct imp));
	tmp = init;
	while (g_global->lst->options[i])
	{

		tmp->next = malloc(sizeof(struct imp));
		opt = ft_strchr(g_global->lst->options[i], '=');
		if (opt)
		{
			len = opt - g_global->lst->options[i];
			tmp->key = ft_substr(g_global->lst->options[i], 0, len);
			if (opt[1] == '"' || opt[1] == '\'')
				tmp->value = ft_substr(g_global->lst->options[i], len + 1 + 1, ft_strlen(opt) - 1 - 2);
			else
				tmp->value = ft_substr(g_global->lst->options[i], len + 1, ft_strlen(g_global->lst->options[i]));

			tmp->egale = 1;
		}
		else
		{
			tmp->key = g_global->lst->options[i];
			tmp->value = NULL;
			tmp->egale = 0;
		}
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (init);
}

void	execute(struct imp **imp)
{
	int i;

	if (!ft_strcmp(g_global->error, "0"))
	{
		if (g_global->lst->mini_cmd != NULL)
			i = redirection(imp);
		else if (g_global->lst->cmd)
		{
			if (g_global->lst->is_builtin == 1)
				is_builtin(imp);
			else
				ft_execve(imp);
		}
	}
}