#ifndef MINISHELL_EXECUTE_H

# define MINISHELL_EXECUTE_H

struct imp {
	char *data;
	char *key;
	char *value;
    int egale;
	struct imp *next;
};

void		execute(struct imp **imp, char **envp);
struct imp	*gere_exp(char **envp);
void        print_export(struct imp **tmp2);
void    	impecho();
struct imp  		**ft_unset(struct imp **imp);
void    			ft_pwd();
int    			ft_cd(struct imp **imp);
void    			ft_exit();
void    print_env(struct imp **imp);
void    ft_execve(struct imp **imp, char **envp);
char   *path_env(struct imp **imp);
void	ex_in_childs(struct imp **imp, char **envp);
void    ft_execve_red(char **envp);
struct imp **manages_options(struct imp **imp);
struct imp *init_options();
int	type_redirection(int fd);
int	redirection(struct imp **imp, char **envp);

#endif
