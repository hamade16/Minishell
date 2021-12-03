#include "../minishell.h"

int	check_forbidden(char *s)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		quote = quote_macro(s[i], quote);

		if ((s[i] == '|' || s[i] == ';' || s[i] == '\\') && quote == 0)
			return (0);
	}
	return (1);
}

// TODO
	// unquote then check last pipe
/*
 * double pipes
 * pipe is the last thing (not quoted)
 */
int	check_pipes(char *l)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (l[++i])
	{
		quote = quote_macro(l[i], quote);

		if (l[i] == '|' && quote == 0) {
			if (l[i + 1] == '|')
				return (0);
		}
	}
	size_t len = ft_strlen(ft_strtrim(l, " "));
	if (ft_strtrim(l, " ")[len - 1] == '|')
		return (0);
	return (1);
}

/*
 * check some errors
 * ||, <>, ><, <<>, >><, <<<, >>>
 * $ [a-zA-Z][?]
 * on error 0
 * on success 1
 */
int	check_redirections(char *s)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		quote = quote_macro(s[i], quote);
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
		}
	}
	return (1);
}

/*
 * on error 0
 * on success 1
 */
int		check_vars(char *s)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		quote = quote_macro(s[i], quote);
		if (s[i] == '$' && quote != 1)
		{
			if (s[i + 1] != '?' && s[i + 1] != '_' && !ft_isalpha(s[i + 1]))
				return (0);
		}
		i++;
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
			if (cmds[i][j] != ' ')
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
int		check_in_redirections(char *cmd)
{
	char	*trimmd;
	size_t	len;

	trimmd = ft_strtrim(cmd, " ");
	len = ft_strlen(trimmd);
	if (len > 0 && (trimmd[len - 1] == '<' || trimmd[len - 1] == '>'))
		return (0);
	return (1);
}
