#include "../minishell.h"

void	print_cmd(t_cmd *c)
{
	if (!c)
		printf("NULL\n--------------\n\n");
	else
	{
		printf("\n\n--------------\n");
		printf("command name   : [%s]\n", c->cmd);
		printf("is implemented : [%d]\n", c->is_builtin);
		if (c->options)
		{
			printf("options are\n");
			for (int i = 0; c->options[i]; i++)
			{
				printf("\t%d [%s]\n", i + 1, c->options[i]);
			}
		}
		if (c->mini_cmd)
		{
			printf("redirections are\n");
			while (c->mini_cmd)
			{
				printf("\t[%d]", c->mini_cmd->redir);
				printf(" [%s] ", c->mini_cmd->filename);
				printf("[%d]\n", c->mini_cmd->ambig);
				c->mini_cmd = c->mini_cmd->next_mini;
			}
		}
		printf("\n--------------\n\n");
		printf("exit status : %s\n", g_global->error);
		printf("\n--------------\n\n");
	}
}
