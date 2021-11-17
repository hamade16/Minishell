#include "../minishell.h"
#include <stdio.h>

/*
 * 0	: Quotes are enclosed
 * else	: Quotes are not enclosed
 */
int	check_quotes(char *str)
{
	size_t	i;
	int		quote;

	// check not closed quote
	i = -1;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '"' && quote == 0)
			quote = 2;
		else if (str[i] == '\'' == quote == 1)
			quote = 0;
		else if (str[i] == '"' && quote == 2)
			quote = 0;
	}
	return (quote);
}

int	check_pipes(char *l)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (l[++i])
	{
		if (l[i] == '\'' && quote == 0)
			quote = 1;
		else if (l[i] == '"' && quote == 0)
			quote = 2;
		else if (l[i] == '\'' == quote == 1)
			quote = 0;
		else if (l[i] == '"' && quote == 2)
			quote = 0;

		if (l[i] == '|' && quote == 0) {
			if (l[i + 1] == '|')
				return (0);
		}
	}
	return (1);
}

int	check_redirections(char *s)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		if (s[i] == '\'' && quote == 0)
			quote = 1;
		else if (s[i] == '"' && quote == 0)
			quote = 2;
		else if (s[i] == '\'' == quote == 1)
			quote = 0;
		else if (s[i] == '"' && quote == 2)
			quote = 0;

		// check some errors
		// ||, <>, ><, <<>, >><, <<<, >>>
		// $ [a-zA-Z][?]

		if (quote == 0)
		{
			if (s[i] == '>')
			{
				if (s[i + 1] == '<')
					return (0);
				if (s[i + 1] == '>')
					if (s[i + 2] == '>')
						return (0);
			}
			else if (s[i] == '<')
			{
				if (s[i + 1] == '>')
					return (0);
				if (s[i + 1] == '<')
					if (s[i + 2] == '<')
						return (0);
			}
			else if (s[i] == '$')
			{
				if (s[i + 1] != '?' || ft_isalpha(s[i + 1]))
					return (0);
			}
		}
	}
	return (1);
}

int		check_empty_pipes(char **cmds)
{
	size_t	i;
	size_t	j;
	int		flag;

	i = -1;
	while (cmds[++i])
	{
		j = -1;
		flag = 0;
		while (cmds[i][++j])
		{
			if (ft_isalnum(cmds[i][j]))
				flag = 1;
		}
		if (!flag)
			return (0);
	}
	return (1);
}

/*
 * redirection at the end
 */
int		check_in_redirections(char **cmds)
{
	size_t	i;
	size_t	j;
	char	*trimmd;
	size_t	len;

	i = -1;
	while (cmds[++i])
	{
		j = 0;
		trimmd = ft_strtrim(cmds[i], " ");
		len = ft_strlen(trimmd);
		if (trimmd[len - 1] == '<' || trimmd[len - 1] == '>')
			return (0);
	}
	return (1);
}

void	ft_append(char ***opt, char *newopt)
{
	size_t	i;
	size_t	len;
	char	**tmp;

	if (*opt == NULL)
	{
		*opt = malloc(sizeof(char *) * 2);
		(*opt)[0] = newopt;
		(*opt)[1] = NULL;
	}
	else
	{
		len = 0;
		while ((*opt)[len])
		{
			len++;
		}

		tmp = *opt;
		*opt = malloc(sizeof(char *) * (len + 1 + 1));
		i = 0;
		while (i < len)
		{
			(*opt)[i] = tmp[i];
			i++;
		}
		(*opt)[i] = newopt;
		(*opt)[i + 1] = NULL;
	}
}

t_mini_cmd	*ft_mini_lstlast(t_mini_cmd *lst)
{
	if (lst)
		while (lst->next_mini)
			lst = lst->next_mini;
	return (lst);
}

void	ft_mini_addback(t_mini_cmd **head, t_mini_cmd *new)
{
	t_mini_cmd	*last;

	if (head && new)
	{
		if (*head)
		{
			last = ft_mini_lstlast(*head);
			last->next_mini = new;
		}
		else
			*head = new;
	}
}

void	ft_fill_it(t_cmd **head, char *line)
{
	size_t		i;
	char		**parts;
	t_cmd		*cmd;
	t_cmd		*tmp;
	t_mini_cmd	*mini;

	i = 0;

	tmp = malloc(sizeof(t_cmd));

	tmp->text = ft_strdup(line);
	tmp->options = NULL;
	tmp->mini_cmd = NULL;

	mini = NULL;

	parts = ft_split_wq(line, ' ');
	while (parts[i])
	{
		if (i == 0) {
			tmp->cmd = parts[i];
			// ft_append(&tmp->options, parts[i]);
			if (!ft_strcmp(tmp->cmd, "export") || !ft_strcmp(tmp->cmd, "echo") ||
				!ft_strcmp(tmp->cmd, "unset") || !ft_strcmp(tmp->cmd, "cd") ||
				!ft_strcmp(tmp->cmd, "pwd") || !ft_strcmp(tmp->cmd, "pwd") ||
				!ft_strcmp(tmp->cmd, "env") || !ft_strcmp(tmp->cmd, "exit"))
				tmp->is_builtin = 1;
			else
				tmp->is_builtin = 0;
		}
		else {
			// is option
			if (parts[i][0] == '-')
				ft_append(&tmp->options, parts[i]);
			// is redirection
			else if (parts[i][0] == '>')
			{

				mini = malloc(sizeof(t_mini_cmd));
				mini->filename = NULL;
				mini->redir = 0;
				mini->next_mini = NULL;

				if (!ft_strcmp(parts[i], ">>")) {
					mini->redir = 3;
				}
				else
					mini->redir = 1;
			}
			// is redirection
			else if (parts[i][0] == '<')
			{
				mini = malloc(sizeof(t_mini_cmd));
				mini->filename = NULL;
				mini->redir = 0;
				mini->next_mini = NULL;

				if (!ft_strcmp(parts[i], "<<")) {
					mini->redir = 4;
				}
				else
					mini->redir = 2;
			}
			// is filename
			else
			{
				if (mini)
				{
					mini->filename = ft_strdup(parts[i]);

					ft_mini_addback(&tmp->mini_cmd, mini);
				}
				else
				{
					ft_append(&tmp->options, parts[i]);
				}
			}
		}
		i++;
	}
	tmp->next_cmd = NULL;

	if (*head == NULL)
		*head = tmp;
	else
	{
		cmd = *head;
		while (cmd->next_cmd)
		{
			cmd = cmd->next_cmd;
		}
		cmd->next_cmd = tmp;
	}
}

// TODO :
	// ls a
void	handle_line(char *line)
{
	size_t		i;
	size_t		j;
	t_cmd		*cmd;
	char		**cmds;

	g_cmds = NULL;
	cmd = NULL;
	i = -1;
	j = -1;
	// ||
	if (!check_quotes(line) || check_pipes(line) || check_redirections(line))
	{
		cmds = ft_split_wq(line, '|');

		// check empty splits
		// check wrong redirections
		if (check_empty_pipes(cmds) || check_in_redirections(cmds))
		{
			while (cmds[++i])
			{
				// get data and fill head
				ft_fill_it(&g_cmds, cmds[i]);
			}
		}
		else
			printf("minishell: syntax error\n");
	}
	else
		printf("minishell: forbidden error\n");
}
