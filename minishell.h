#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include "parse/minishell_parse.h"
# include "execute/minishell_execute.h"
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
t_lst_cmd		g_lst_cmds;

#endif
