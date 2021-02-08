/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:04:31 by keddib            #+#    #+#             */
/*   Updated: 2021/02/08 17:57:39 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_stack		*new_element(char character)
{
	t_stack		*new_element;

	if (!(new_element = (t_stack *)malloc(sizeof(t_stack))))
		return (NULL);
	new_element->character = character;
	new_element->meta = 0;
	new_element->special = 0;
	return (new_element);
}

void		push(t_list **stack, char character)
{
	t_stack		*stack_element;
	t_list		*node;

	stack_element = new_element(character);
	node = ft_lstnew(stack_element);
	ft_lstadd_front(stack, node);
	is_metacharacter(stack);
}

char		pop(t_list **stack)
{
	t_list		*tmp;
	char		c;

	if (*stack)
	{
		c = ((t_stack *)((*stack)->content))->character;
		tmp = (*stack)->next;
		free((*stack)->content);
		free((*stack));
		(*stack) = tmp;
		return (c);
	}
	return ('\0');
}

char		top_stack(t_list **stack)
{
	if (*stack)
		return (((t_stack *)(*stack)->content)->character);
	return ('\0');
}
