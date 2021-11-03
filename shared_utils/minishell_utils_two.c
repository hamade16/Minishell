#include "../minishell.h"

t_lst_cmd	*ft_lstmap(t_lst_cmd *lst, void *(*f)(void *), void (*del)(void *))
{
	t_lst_cmd	*nlst;
	t_lst_cmd	*nhead;

	nhead = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			nlst = ft_lstnew(f(lst->content));
			if (!nlst)
			{
				ft_lstclear(&nhead, del);
				return (NULL);
			}
			ft_lstadd_back(&nhead, nlst);
			lst = lst->next;
		}
	}
	return (nhead);
}

void	ft_lstclear(t_lst_cmd **lst, void (*del)(void *))
{
	t_lst_cmd	*tmp;
	t_lst_cmd	*l;

	if (lst && del)
	{
		l = *lst;
		while (l)
		{
			tmp = l;
			l = l->next;
			del(tmp->content);
			free(tmp);
		}
		*lst = NULL;
	}
}

void	ft_lstdelone(t_lst_cmd *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

void	ft_lstiter(t_lst_cmd *lst, void (*f)(void *))
{
	while (lst && f)
	{
		f(lst->content);
		lst = lst->next;
	}
}
