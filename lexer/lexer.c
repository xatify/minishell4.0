/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 07:33:33 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/25 14:37:06 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ret_hundle_meta(t_list **stack, t_list **tokens, int append)
{
	if (!empty_stack(stack, tokens))
		return (0);
	pop(stack);
	if (append)
		pop(stack);
	return (1);
}

int	handle_metacharacter(t_list **stack, t_list **tokens, char **input_cmd)
{
	char		top;
	int			append;

	append = 0;
	top = top_stack(stack);
	pop(stack);
	if ((*stack) && !empty_stack(stack, tokens))
		return (0);
	push(stack, top);
	if ((top == '>' && **input_cmd == '>'))
	{
		append = 1;
		push(stack, *(*input_cmd)++);
	}
	else if (top == '<' && **input_cmd == '<')
	{
		append = 2;
		push(stack, *(*input_cmd)++);
	}
	else if (is_meta(**input_cmd))
	{
		ft_lstclear(stack, free);
		ft_lstclear(tokens, free_token);
		return (0);
	}
	return (ret_hundle_meta(stack, tokens, append));
}

int	handle_end_token(t_list **stack, t_list **tokens)
{
	if (*stack != NULL)
	{
		pop(stack);
		if (*stack != NULL)
			empty_stack(stack, tokens);
		return (1);
	}
	return (0);
}
