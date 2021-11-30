#include "../minishell.h"

int	quote_macro(char c, int q)
{
	if (c == '\'' && q == 0)
		return (1);
	else if (c == '"' && q == 0)
		return (2);
	else if (c == '\'' == q == 1)
		return (0);
	else if (c == '"' && q == 2)
		return (0);
	return (q);
}

/*
 * 0	: Quotes are enclosed
 * else	: Quotes are not enclosed
 */
int	check_quotes(char *s)
{
	size_t	i;
	int		quote;

	// check not closed quote
	i = -1;
	quote = 0;
	while (s[++i])
	{
		quote = quote_macro(s[i], quote);
	}
	if (quote != 0)
		g_global->error = "256";
	return (!quote);
}

int	check_quotes_ind(char *s, size_t len)
{
	size_t	i;
	int		quote;

	// check not closed quote
	i = -1;
	quote = 0;
	while (s[++i] && i < len + 1)
	{
		quote = quote_macro(s[i], quote);
	}
	return (quote);
}
