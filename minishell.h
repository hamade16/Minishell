/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:40:22 by abel-haj          #+#    #+#             */
/*   Updated: 2021/12/07 17:40:24 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
    
# include "libft/libft.h"
# include "execute/minishell_execute.h"
# include "parse/minishell_parse.h"
# include <stdio.h>
// malloc, ...
# include <stdlib.h>
// write, execve, ...
# include <unistd.h>
// open, ...
# include <fcntl.h>
// wait
# include <sys/wait.h>
// readline, add_history
# include <readline/readline.h>
# include <readline/history.h>

# include <dirent.h>

// Global Variable
t_global		*g_global;

#endif
