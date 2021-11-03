#include "../minishell.h"

// typedef struct s_mini_cmd {
// 	char				*filename;
// 	int					redir; // '<'. '<<'
// 	struct s_mini_cmd	*next_mini;
// } t_mini_cmd;

// typedef struct s_cmd {
// 	char				*text;
// 	char				*cmd;
// 	char				**options;
// 	char				is_builtin;
// 	struct s_mini_cmd	*mini_cmd;
// 	struct s_cmd		*next_cmd;
// }				t_cmd;

t_cmd	*cas_one()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	// ls -la > a
	cmd->text = "ls -la > a";
	cmd->cmd = "ls";

	cmd->options = malloc(sizeof(char *) * 2);
	cmd->options[0] = "-la";
	cmd->options[1] = NULL;

	cmd->is_builtin = 1;

	cmd->mini_cmd = malloc(sizeof(t_mini_cmd));
	cmd->mini_cmd->filename = "a";
	cmd->mini_cmd->redir = ">";
	cmd->mini_cmd->next_mini = NULL;

	cmd->next_cmd = NULL;
	return (cmd);
}

t_cmd	*cas_two()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	// ls -la > a
	cmd->text = "echo -n string | cat -e";
	cmd->cmd = "echo";
	cmd->options = malloc(sizeof(char *) * 3);
	cmd->options[0] = "-n";
	cmd->options[1] = "string";
	cmd->options[2] = NULL;
	cmd->is_builtin = 0;
	cmd->mini_cmd = NULL;

	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	cmd2->cmd = "echo";
	cmd2->options = malloc(sizeof(char *) * 2);
	cmd2->options[0] = "-n";
	cmd2->options[1] = NULL;
	cmd2->is_builtin = 1;
	cmd2->mini_cmd = NULL;

	cmd->next_cmd = cmd2;
	return (cmd);
}

void	execute(void)
{
	t_cmd *cmd = cas_one();
	// t_cmd *cmd = cas_two();
}