/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:08:45 by keddib            #+#    #+#             */
/*   Updated: 2021/06/19 12:09:15 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	special(t_list *stack)
{
	int		special;

	special = 0;
	stack = stack->next;
	while (stack)
	{
		if (((t_stack *)(stack->content))->character == 0x5c)
		{
			special++;
			stack = stack->next;
		}
		else
			break ;
	}
	return (special % 2);
}
