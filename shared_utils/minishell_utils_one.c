#include "../minishell.h"

t_lst_cmd	*ft_lstnew(void *content)
{
	t_lst_cmd	*list;

	list = malloc(sizeof(t_lst_cmd));
	if (list)
	{
		list->content = content;
		list->next = NULL;
	}
	return (list);
}

void	ft_lstadd_back(t_lst_cmd **alst, t_lst_cmd *new)
{
	t_lst_cmd	*last;

	if (alst && new)
	{
		if (*alst)
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}

void	ft_lstadd_front(t_lst_cmd **alst, t_lst_cmd *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

int	ft_lstsize(t_lst_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_lst_cmd	*ft_lstlast(t_lst_cmd *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
