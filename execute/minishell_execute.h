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

#endif
