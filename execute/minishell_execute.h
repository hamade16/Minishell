#ifndef MINISHELL_EXECUTE_H

# define MINISHELL_EXECUTE_H

struct imp {
	char *data;
	char *key;
	char *value;
    int egale;
	struct imp *next;
};

void		execute(struct imp **imp);
struct imp	*gere_exp(char **envp);
void        print_export(struct imp **tmp2);
void    	impecho();
struct imp  		**ft_unset(struct imp **imp);
void    			ft_pwd(void);
int    			ft_cd(struct imp **imp);
void    			ft_exit(void);
void    print_env(struct imp **imp);
int    ft_execve(struct imp **imp);
char   *path_env(struct imp **imp);
void	ex_in_childs(struct imp **imp);
struct imp **manages_options(struct imp **imp);
struct imp *init_options();
int	type_redirection(int fd);
int	redirection(struct imp **imp);
char	**ft_convert_to_arr(struct imp *env_lst);
void	is_builtin(struct imp **imp);
void	ft_error(char *str1, char *str2, char *str3);
void	ex_with_redriction(struct imp **imp);
int		red_out(void);
void	dup_red(int a, int b);
int		red_in(void);
//int		red_herdog(t_mini_cmd *c);
int	is_execitable(char **env_conv);
void	ex_execve(char *pathname, char **env_conv);
int	inexecutable(struct imp **imp, char **env_conv);
char	*research_path(struct imp **imp);

#endif
