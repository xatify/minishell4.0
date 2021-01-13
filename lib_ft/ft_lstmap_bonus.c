/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 20:49:50 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/21 19:20:54 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*l;
	int		i;

	l = lst;
	i = ft_lstsize(l);
	while (i--)
	{
		ft_lstadd_back(&new_list, ft_lstnew(f(l->content)));
		if (!ft_lstlast(new_list))
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		l = l->next;
	}
	return (new_list);
}
