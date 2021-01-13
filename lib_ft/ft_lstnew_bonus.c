/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:11:07 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/21 18:50:43 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
