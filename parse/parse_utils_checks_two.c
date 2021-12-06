#include "../minishell.h"

int	check_redirections_macro(char *s, int i)
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
	return (1);
}

/*
 * check some errors
 * <>, ><, <<>, >><, <<<, >>>
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
			if (s[i] == '>' || s[i] == '<')
			{
				if (check_redirections_macro(s, i) == 0)
					return (0);
			}
		}
	}
	return (1);
}

/*
 * redirection at the end
 */
int	check_end_redirections(char *cmd)
{
	char	*trimmd;
	size_t	len;

	trimmd = ft_strtrim(cmd, " ");
	len = ft_strlen(trimmd);
	if (len > 0 && (trimmd[len - 1] == '<' || trimmd[len - 1] == '>'))
		return (0);
	return (1);
}
