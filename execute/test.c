/*#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>



int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*f_string;
	unsigned char	*s_string;

	i = 0;
	f_string = (unsigned char *)s1;
	s_string = (unsigned char *)s2;
	while (f_string[i] && s_string[i])
	{
		if (f_string[i] != s_string[i])
			return (f_string[i] - s_string[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (*(s + i))
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		len1;
	int		len2;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(s3 = (char*)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		s3[len1 + i] = s2[i];
		i++;
	}
	s3[i + len1] = '\0';
	return (s3);
}

struct imp {
	char *data;
	char *key;
	char *value;
	struct imp *next;
};

struct otpt {
	char *data;
	char *key;
	char *value;
	struct otpt *next;
};


char	*ft_strchr(const char *s, int c)
{
	if (c == '\0')
		return ((char*)s + ft_strlen((char*)s));
	while (*s && *s != c)
		s++;
	if (*s == '\0')
		return (0);
	return ((char *)s);
}

static	int		ft_count_split(char const *str, char c)
{
	int count;
	int j;

	count = 0;
	j = 0;
	while (*str != '\0')
	{
		if (*str == c)
			j = 0;
		else if (j == 0)
		{
			j = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static	int		ft_wsp(char const *str, int i, char c)
{
	int len;

	len = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static	void	*free_t(char **split, int j)
{
	while (j--)
		free(split[j]);
	free(split);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**split;
	int		k;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (!(split = (char**)malloc(sizeof(char*) * (ft_count_split(s, c) + 2))))
		return (NULL);
	while (j < ft_count_split(s, c))
	{
		while (s[i] == c)
			i++;
		if (!(split[j] = (char*)malloc(sizeof(char) * (ft_wsp(s, i, c) + 1))))
			return (free_t(split, j));
		k = 0;
		while (s[i] != c && s[i] != '\0')
			split[j][k++] = s[i++];
		split[j][k] = '\0';
		j++;
	}
	split[j] = NULL;
	return (split);
}

int	len_key(char *s)
{
	int i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}

void	chick_egale(char *s)
{
	size_t len;
	char *s2;
	if ((ft_strcchr(s, '=') != 0) && (!s))
	{	
		int i;
		i = 0;
		while (s[i] != '=')
			i++;
		//s2 = ft_substr(s, 0, i);
		return (s2);
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	len = (start > ft_strlen(s) ? 0 : len);
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

void print_export(struct imp *tmp2)
{
	while (tmp2->next != NULL)
	{
		if(tmp2->value != NULL)
		{
			printf ("declare -x ");
			printf("%s", tmp2->key);
			printf ("=\"");
			printf("%s", tmp2->value);
			printf("\"\n");
		}
		else
		{
			printf ("declare -x ");
			printf("%s", tmp2->key);
		}
		tmp2 = tmp2->next;
	}
}

struct imp	*gere_exp(char **envp)
{	struct imp *imp;
	struct imp *tmp;
	struct imp *tmp2;
	int i;
	int len;

	i = 0;
	len = 0;
	imp = malloc(sizeof(struct imp));
	tmp = imp;
	while (envp[i])
	{

		tmp->next = malloc(sizeof(struct imp));
		if (ft_strchr(envp[i], '='))
		{
			len = ft_strchr(envp[i], '=') - envp[i];
			tmp->key = ft_substr(envp[i], 0, len);
			tmp->value = ft_substr(envp[i], len + 1, ft_strlen(envp[i]));
		}
		else 
		{
			//len = len_key(envb[i]);
			//printf ("%d\n", len);
			//tmp->key = (char*)malloc(sizeof(char));
			tmp->key = envp[i];
			tmp->value = NULL;
		}
		//tmp->key = chick_egale(envb[i]);
		//tmp->data = ft_strjoin("declare -x ", envb[i]);
		//printf ("%s", tmp->key);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	tmp2 = imp;
	while (tmp2->next != NULL)
	{
		printf ("declare -x ");
		printf("%s", tmp2->key);
		printf ("=\"");
		printf("%s", tmp2->value);
		printf("\"\n");
		tmp2 = tmp2->next;
	}
	return (imp);
}

void	imp_export(char **line, struct imp *imp, int nb)
{
	int i;
	struct imp *tmp;
	int len;
	int len1;
	struct imp *tmp1;
	int j;

	tmp1 = imp;
	tmp1 = imp;
	i = 0;
	while (i < nb)
	{
		len1 = ft_strlen(line[i]);
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->key, line[i]))
			{
				j = 0;
				while (line[i][j])
				{
					if (ft_strchr(line[i][j], '='))
					{
						len = len_key(line[i][j]);
						tmp->key = ft_substr(line[i][j], 0, len);
						if (len1 > len)
							tmp->value = ft_substr(line[i][j], len + 1, (len1 - len));
					}
				}
			}
		}
		i++;
	}
	print_export(tmp);
}

int main(int ac, char **av, char **envp)
{
	struct imp *imp;
	char **line;
	int i;
	struct otpt otpt;

	imp = gere_exp(envp);
	// imp->data = "hamada";
	// imp->next = NULL;
	//printf ("%s\n", imp->data);
	// tmp = tmp->next;
	// tmp->data = "oubeid";
	// tmp->next = NULL;
	// tmp2 = imp;
	//for (;tmp2 != NULL; tmp2 = tmp2->next)

	while (1)
	{
	i = 0;
	line = ft_split(readline("minishell "), ' ');
	while (line[i])
		i++;
	
	imp_export(line, imp, i);
	//}
    // if (chdir(av[1]) == 0){
    //     // perror("cd: ");
    //     perror("cd ");
    // }
    // else 
    // {
	
        //chdir(av[1]);

        //printf("%s\n", getcwd(av[1], 100));
    //}
    
    //printf("%s\n", getcwd(av[1], 100));
}*/