/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:57:02 by keddib            #+#    #+#             */
/*   Updated: 2021/02/06 17:58:11 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*tokenizer(int error, t_list **tokens, t_list **stack)
{
	if (error)
	{
		ft_lstclear(tokens, free);
		ft_lstclear(stack, free);
		return(NULL);
	}
	if (!(*tokens))
	{
		if ((*stack))
			ft_lstclear(stack, free);
		ft_putstr_fd("error while parsing !\n", 1);
		return (NULL);
	}
	if (identify_all_tokens(*tokens))
		return (*tokens);
	ft_lstclear(tokens, free);
	if ((*stack))
			ft_lstclear(stack, free);
	ft_putstr_fd("error while parsing !\n", 1);
	return (NULL);
}

t_list	*lexer(char *input_cmd)
{
	t_list		*tokens;
	t_list		*stack;
	int			error;

	tokens = NULL;
	stack = NULL;
	while(TRUE)
	{
		error = 0;
		push(&stack, *input_cmd++);
		if (top_stack(&stack) == '\'' || top_stack(&stack) == '\"')
			if (!handle_quotes(&stack, &input_cmd, &error))
				break ;
		if (top_stack(&stack) == ' ' || top_stack(&stack) == '\t')
		{
			if (!handle_space(&stack, &tokens, &error))
				break ;
			continue ;
		}
		if (handle_meta(&stack, &tokens, &input_cmd))
			break ;
	}
	return (tokenizer(error, &tokens, &stack));
}
