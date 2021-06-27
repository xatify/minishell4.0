/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:57:02 by keddib            #+#    #+#             */
/*   Updated: 2021/06/26 20:00:20 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*tokenizer(int error, t_list **tokens, t_list **stack)
{
	if (error)
	{
		ft_lstclear(tokens, free_token);
		ft_lstclear(stack, free);
		return (NULL);
	}
	if (!(*tokens))
	{
		if ((*stack))
			ft_lstclear(stack, free);
		return (NULL);
	}
	if (identify_all_tokens(*tokens))
		return (*tokens);
	ft_lstclear(tokens, free);
	if ((*stack))
		ft_lstclear(stack, free);
	return (NULL);
}

int	handle_meta(t_list **stack, t_list **tokens, char **input_cmd)
{
	if (*stack && ((t_stack *)((*stack)->content))->meta)
	{
		if (!handle_metacharacter(stack, tokens, input_cmd))
			return (1);
	}
	else if (top_stack(stack) == '\0')
		if (handle_end_token(stack, tokens))
			return (1);
	return (0);
}

int	handle_space(t_list **stack, t_list **tokens, int *error)
{
	pop(stack);
	if (top_stack(stack) != '\0' && *stack != NULL)
	{
		if (!empty_stack(stack, tokens))
		{
			*error = 1;
			return (0);
		}
	}
	*error = 0;
	return (1);
}

int	handle_quotes(t_list **stack, char **input_cmd, int *error, char quote)
{
	int	second_quote;

	*error = 0;
	second_quote = 0;
	while (**input_cmd)
	{
		push(stack, *(*input_cmd)++);
		if (top_stack(stack) == quote)
		{
			second_quote = 1;
			break ;
		}
	}
	if (!second_quote || (**input_cmd == '\0' && top_stack(stack) != quote))
	{
		*error = 1;
		return (0);
	}
	return (1);
}

t_list	*lexer(char *input_cmd, int *error)
{
	t_list		*tokens;
	t_list		*stack;

	tokens = NULL;
	stack = NULL;
	while (TRUE)
	{
		*error = 0;
		push(&stack, *input_cmd++);
		if (top_stack(&stack) == '\'' || top_stack(&stack) == '\"')
			if (!handle_quotes(&stack, &input_cmd, error, top_stack(&stack)))
				break ;
		if (top_stack(&stack) == ' ' || top_stack(&stack) == '\t')
		{
			if (!handle_space(&stack, &tokens, error))
				break ;
			continue ;
		}
		if (handle_meta(&stack, &tokens, &input_cmd))
			break ;
	}
	return (tokenizer(*error, &tokens, &stack));
}
