#ifndef MINISHELL_PARSE_H

# define MINISHELL_PARSE_H

/*
 * CMD[*1, *2, *3, NULL]
 * TYPE :
 *   1 : redirection
 *   2 :
 * TEXT :
 *   command as it is
 * REDIR_BEFORE :
 * REDIR_AFTER :
 *   1 : <
 *   2 : >
 *   3 : <<
 *   4 : >>
 * IS_BUILTIN :
 *   0 OR 1
 */
/*

cmd < 'pwd' > test.txt
['-s', '-n']
['string']

echo -s -n string


[NULL]
['string', '-s', '-n']

echo string -s -n


echo string
*/

typedef struct s_mini_cmd {
	char				*filename;
	int					redir;
	struct s_mini_cmd	*next;
} t_mini_cmd;

typedef struct s_cmd {
	char				*text;
	char				*cmd;
	char				**options;
	char				is_builtin;
	struct s_mini_cmd	*mini_cmd;
}				t_cmd;

typedef struct s_lst_cmd {
	t_cmd				*content;
	struct s_lst_cmd	*next;
}				t_lst_cmd;

t_lst_cmd		handle_line(char *s);
void			ft_lstprint(t_lst_cmd *list);
t_lst_cmd		*ft_lstnew(void *content);
void			ft_lstadd_front(t_lst_cmd **alst, t_lst_cmd *new);
int				ft_lstsize(t_lst_cmd *lst);
t_lst_cmd		*ft_lstlast(t_lst_cmd *lst);
void			ft_lstadd_back(t_lst_cmd **alst, t_lst_cmd *new);
void			ft_lstdelone(t_lst_cmd *lst, void (*del)(void *));
void			ft_lstclear(t_lst_cmd **lst, void (*del)(void *));
void			ft_lstiter(t_lst_cmd *lst, void (*f)(void *));
t_lst_cmd		*ft_lstmap(t_lst_cmd *l, void *(*f)(void *), void (*d)(void *));

char			**ft_split_wq(char *s, char c);

#endif
