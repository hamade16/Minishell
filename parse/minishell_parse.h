/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:11:48 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 23:05:06 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H

# define MINISHELL_PARSE_H

typedef struct s_mini_cmd {
	char				*filename;
	int					redir;
	int					ambig;
	struct s_mini_cmd	*next_mini;
}				t_mini_cmd;

typedef struct s_cmd {
	char				*cmd;
	char				**options;
	char				is_builtin;
	struct s_mini_cmd	*mini_cmd;
	char				*error;
}				t_cmd;

typedef struct s_globl {
	t_cmd				*lst;
	char				*pathname;
	char				*error;
	int					child_ex;
	int					her_ex;
	int					sig_exdeja;
	int					sig_ex;
}				t_global;

typedef struct s_norm {
	size_t		i;
	size_t		j;
}				t_norm;

void		handle_line(char *s, t_imp *env);
t_mini_cmd	*ft_mini_lstlast(t_mini_cmd *lst);
void		ft_mini_addback(t_mini_cmd **head, char *f, int r, int a);

int			ft_is_builtin(char *cmd);
void		ft_append(char ***option, char *newoption);

char		**ft_split_wq(char *s, char c, size_t i, size_t j);
int			check_quotes_ind(char *str, size_t len);
int			check_quotes(char *s);
int			quote_macro(char c, int q);
void		ft_expand_data(t_cmd **cmd, t_imp *env);
char		*expand_it(char *s, t_imp *env, size_t size);
void		ft_unquote(t_cmd **cmd);
char		*ft_remove_quotes(char *str);
void		expand_it_init(size_t *i, size_t *size, int *quote);
int			expand_it_cmp_macro(char *s, size_t i, int quote);
void		expand_it_count(char *s, size_t *i, size_t *size, t_imp *e);
void		expand_cmp_iter_macro(char *s, size_t *i, size_t *size);
t_norm		expand_it_repl(char *s, t_norm norm, char **r, t_imp *e);
void		expand_repl_iter_macro(char *s, char **r, size_t *i, size_t *j);
void		ft_extract_it(t_cmd **head, char *line, int redir);

int			check_forbidden(char *s);
int			check_pipes(char *l);
int			check_redirections(char *s);
int			check_vars(char *s);
int			check_empty_pipes(char **cmds);
int			check_end_redirections(char *cmd);

void		*pmalloc(size_t size);
void		ft_exit_malloc(void);
char		*ft_substr_wrap(char const *s, unsigned int start, size_t len);
char		*ft_strdup_wrap(const char *s);

int			handlsignal_helper(void);

// #######
void		print_cmd(t_cmd *c);
// #######

#endif
