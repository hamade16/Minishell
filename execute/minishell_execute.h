/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:49:27 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/07 07:56:06 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTE_H

# define MINISHELL_EXECUTE_H

typedef struct s_imp {
	char			*key;
	char			*value;
	int				egale;
	struct s_imp	*next;
}					t_imp;

void				execute(t_imp **imp);
t_imp				*gere_exp(char **envp);
void				print_export(t_imp **tmp2);
void				impecho(int j);
t_imp				**ft_unset(t_imp **imp);
void				ft_pwd(t_imp **imp);
int					ft_cd(t_imp **imp);
void				ft_exit(void);
void				print_env(t_imp **imp);
int					ft_execve(t_imp **imp);
char				*path_env(t_imp **imp);
void				ex_in_childs(t_imp **imp);
t_imp				**manages_options(t_imp **imp);
t_imp				*init_options(void);
int					type_redirection(int fd, t_imp *env);
int					redirection(t_imp **imp);
char				**ft_convert_to_arr(t_imp *env_lst);
void				is_builtin(t_imp **imp);
void				ft_error(char *str1, char *str2, char *str3);
void				ex_with_redriction(t_imp **imp);
int					red_out(char *filename, int ambig);
void				dup_red(int a, int b);
int					red_in(char *filename, int ambig);
int					is_execitable(char **env_conv);
void				ex_execve(char *pathname, char **env_conv);
int					inexecutable(t_imp **imp, char **env_conv);
char				*research_path(t_imp **imp);
int					red_herdog(char *filename, t_imp *env);
int					macro_typered(int fd);
void				is_file(int wstatus);
void				macro_print(char *str1, char *str2, int cmpt);
void				remplir_imp(t_imp **imp, t_imp *tmp1);
void				var_exist(t_imp **tmp, t_imp *tmp1);
void				imp_env(t_imp **tmp, char **envp, int i);
void				free_list(t_imp *init);
void				free_double(char **env_var);

#endif
