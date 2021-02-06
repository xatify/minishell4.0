/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:08:35 by keddib            #+#    #+#             */
/*   Updated: 2021/02/06 17:16:31 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		handle_dq_back_slack(t_list **stack, char **token, int *first_back_slash)
{
	if (!(*first_back_slash))
	{
		*first_back_slash = 1;
		push(stack, **token);
		((t_stack *)((*stack)->content))->special = 1;
	}
	else if (((t_stack *)((*stack)->content))->special)
		((t_stack *)((*stack)->content))->special = 0;
	else if (!(((t_stack *)((*stack)->content))->special))
	{
		push(stack, **token);
		((t_stack *)((*stack)->content))->special = 1;
	}
}

int			handle_dq_dollar_sign(t_list **stack, char **token, t_data *data)
{
	if ((*stack) && ((t_stack *)((*stack)->content))->special)
	{
		pop(stack);
		push(stack, **token);
		return (0);
	}
	else
	{
		(*token)++;
		expand_dollar_sign(token, stack, data, NULL);
		return (1);
	}
}

int			expand_double_quotes(t_list **stack, char **token, t_data *data)
{
	int		first_back_slash;

	pop(stack);
	first_back_slash = 0;
	while (TRUE)
	{
		if (**token != '$' && **token != '\\')
		{
			if (handle_dq_non_special(stack, token))
				break;
		}
		else if (**token == '\\')
			handle_dq_back_slack(stack, token, &first_back_slash);
		else if (**token == '$')
		{
			if (handle_dq_dollar_sign(stack, token, data))
				continue;
		}
		(*token)++;
	}
	return(1);
}

int			expand_single_quotes(t_list **stack, char **token)
{
	pop(stack);
	while(**token != '\'')
		push(stack, *(*token)++);
	(*token)++;
	return (1);
}

int			expand_quotes(t_list **stack, char **token, t_data *data)
{
	if (top_stack(stack) == '\'')
	{
		if (!expand_single_quotes(stack, token))
			return (0);
	}
	else if (!expand_double_quotes(stack, token, data))
		return (0);
	return (1);
}
