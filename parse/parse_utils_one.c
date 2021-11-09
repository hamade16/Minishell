#include "../minishell.h"

int	is_quoted(char *qs)
{
	size_t	i;
	int		quote;

	quote = 0;
	i = -1;
	while (qs[++i])
	{
		if (qs[i] == '\'' && quote == 0)
			quote = 1;
		else if (qs[i] == '"' && quote == 0)
			quote = 2;
		else if (qs[i] == '\'' == quote == 1)
			quote = 0;
		else if (qs[i] == '"' && quote == 2)
			quote = 0;
	}
	return (quote);
}

static size_t	count_splitted_wq(char *s, char c)
{
	size_t	i;
	size_t	pipes;
	int		quote;

	i = -1;
	pipes = 0;
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
		if (s[i] == c && quote == 0)
			pipes++;
	}
	return (pipes);
}

// TODO :
	// reduce variable numbers
	// reduce lines
char	**ft_split_wq(char *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	i;
	size_t	j;
	size_t	len;
	int		quote;
	char	**result;

	i = -1;
	j = 0;
	start = 0;
	quote = 0;
	len = count_splitted_wq(s, c) + 1;
	result = (char **)malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	while (s[++i] && j < len)
	{
		if (s[i] == '\'' && quote == 0)
			quote = 1;
		else if (s[i] == '"' && quote == 0)
			quote = 2;
		else if (s[i] == '\'' == quote == 1)
			quote = 0;
		else if (s[i] == '"' && quote == 2)
			quote = 0;

		if (quote == 0 && s[i] == c)
		{
			end = i;
			result[j] = ft_substr(s, start, i - start);
			start = i + 1;
			j++;
		}
	}
	if (len == 1)
		result[j] = ft_substr(s, 0, i);
	else
		result[j] = ft_substr(s, end + 1, i - end - 1);
	result[len] = NULL;
	return (result);
}
