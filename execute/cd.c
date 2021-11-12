#include "../minishell.h"

void    imp_cd()
{
    chdir(g_cmds->options[0]);
}