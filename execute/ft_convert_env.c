#include "../minishell.h"

static size_t	ft_get_env_size(struct imp *env_lst)
{
	size_t	len;

	len = 0;
	while (env_lst)
	{
		env_lst = env_lst->next;
		len++;
	}
	return (len);
}

char	**ft_convert_to_arr(struct imp *env_lst)
{
	char	**env_arr;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	len = ft_get_env_size(env_lst);
	env_arr = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		j = 0;
		printf("\n%s=%s\n", env_lst->key, env_lst->value);
		env_arr[i] = malloc(sizeof(char)
				* (ft_strlen(env_lst->key)
					+ ft_strlen(env_lst->value) + 1 + 1));
		env_arr[i][j] = 0;
		ft_strlcat(env_arr[i], env_lst->key, ft_strlen(env_lst->key) + 1);
		ft_strlcat(env_arr[i], "=", ft_strlen(env_lst->key) + 1 + 1);
		ft_strlcat(env_arr[i], env_lst->value,
			ft_strlen(env_lst->key) + ft_strlen(env_lst->value) + 1 + 1);
		printf("%s\n", env_arr[i]);
		env_lst = env_lst->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
