#include "../minishell.h"

char	*ft_expand_norm(char *str, t_imp *env)
{
	char	*tmp;

	tmp = str;
	str = expand_it(str, env);
	free(tmp);
	return (str);
}

void	ft_expand_data(t_cmd **cmd, t_imp *env)
{
	int			i;
	t_mini_cmd	*mini;

	if ((*cmd)->cmd)
	{
		(*cmd)->cmd = ft_expand_norm((*cmd)->cmd, env);
	}
	if ((*cmd)->options)
	{
		i = 0;
		while ((*cmd)->options[i])
		{
			(*cmd)->options[i] = ft_expand_norm((*cmd)->options[i], env);
			i++;
		}
	}
	mini = (*cmd)->mini_cmd;
	while (mini)
	{
		mini->filename = ft_expand_norm(mini->filename, env);
		if (ft_strlen(mini->filename) <= 0)
			mini->ambig = 1;
		mini = mini->next_mini;
	}
}

size_t	expand_it_one_norm(char *key_var, char *key_lst, char *val_lst)
{
	if (ft_strcmp(key_var, key_lst) == 0)
		return (ft_strlen(val_lst));
	return (0);
}

void	expand_it_count(char *s, size_t *i, size_t *size, t_imp *head)
{
	size_t	var_size;
	char	*var_key;

	(*i) += 2;
	var_size = 2;
	if (s[(*i) - 1] != '?')
	{
		while (ft_isalnum(s[*i]) || s[*i] == '_')
		{
			(*i)++;
			var_size++;
		}
	}
	var_key = ft_substr_wrap(s, *i - var_size + 1, var_size - 1);
	while (head)
	{
		(*size) += expand_it_one_norm(var_key, head->key, head->value);
		head = head->next;
	}
	if (ft_strcmp(var_key, "?") == 0)
		(*size) += ft_strlen(g_global->error);
	free(var_key);
}

void	expand_it_rep(char *s, size_t *i, size_t *j, char **res, t_imp *head)
{
	size_t	var_size;
	char	*var_key;

	(*i) += 2;
	var_size = 2;
	if (s[*i - 1] != '?')
	{
		while (ft_isalnum(s[*i]) || s[*i] == '_')
		{
			(*i)++;
			var_size++;
		}
	}
	var_key = ft_substr_wrap(s, (*i) - var_size + 1, var_size - 1);
	while (head)
	{
		if (ft_strcmp(var_key, head->key) == 0)
		{
			ft_strlcpy(*res + *j, head->value, ft_strlen(head->value) + 1);
			*j += ft_strlen(head->value);
		}
		head = head->next;
	}
	if (ft_strcmp(var_key, "?") == 0)
	{
		ft_strlcpy(*res + *j, g_global->error, ft_strlen(g_global->error) + 1);
		*j += ft_strlen(g_global->error);
	}
	free(var_key);
}

int	expand_it_cmp_macro(char *s, size_t i, int quote)
{
	if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_'
			|| s[i + 1] == '?') && quote != 1)
		return (1);
	return (0);
}

// TODO:
	// norm
char	*expand_it(char *s, t_imp *env)
{
	size_t	i;
	size_t	j;
	size_t	size;
	int		quote;
	char	*res;

	i = 0;
	size = 0;
	quote = 0;
	while (s[i])
	{
		quote = quote_macro(s[i], quote);
		if (expand_it_cmp_macro(s, i, quote))
			expand_it_count(s, &i, &size, env);
		if (s[i])
		{
			size++;
			i++;
		}
	}
	i = 0;
	j = 0;
	quote = 0;
	res = pmalloc(sizeof(char) * size + 1);
	while (s[i])
	{
		quote = quote_macro(s[i], quote);
		if (expand_it_cmp_macro(s, i, quote))
			expand_it_rep(s, &i, &j, &res, env);
		else
		{
			res[j] = s[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	return (res);
}
