/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_methodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 08:01:54 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 12:18:52 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	t_list	*node;
	t_list	*nex;

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
	t_list	*tmp;

	if (!(*alst))
		(*alst) = new;
	else
	{
		tmp = ft_lstlast(*alst);
		tmp->next = new;
	}
}
