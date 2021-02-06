/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_methods_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:51:17 by keddib            #+#    #+#             */
/*   Updated: 2021/02/05 17:51:54 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
