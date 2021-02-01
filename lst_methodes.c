/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_methodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 08:01:54 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/01 17:51:47 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list *new;

	new = (struct s_list *)malloc(sizeof(struct s_list));
	if (new)
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}

int		ft_lstsize(t_list *lst)
{
	if (lst == NULL)
		return (0);
	return (1 + ft_lstsize(lst->next));
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list *node;

	node = lst;
	if (!lst)
		return (lst);
	if (!node->next)
		return (node);
	return (ft_lstlast(node->next));
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
		lst = NULL;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *node;
	t_list *nex;

	node = (*lst);
	while (node && del)
	{
		nex = node->next;
		ft_lstdelone(node, del);
		node = nex;
	}
	(*lst) = NULL;
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!(*alst))
		(*alst) = new;
	else
	{
		new->next = (*alst);
		(*alst) = new;
	}
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (!(*alst))
		(*alst) = new;
	else
		ft_lstlast((*alst))->next = new;
}

