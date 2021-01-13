/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:26:53 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/21 19:02:22 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
