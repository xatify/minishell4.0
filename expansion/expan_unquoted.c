/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_unquoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:09:32 by keddib            #+#    #+#             */
/*   Updated: 2021/02/08 15:37:27 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		handle_ut_back_slash(t_list **stack, char **token, int *f_b_slash)
{
	if (!(*f_b_slash))
	{
		*f_b_slash = 1;
		push(stack, **token);
		((t_stack *)((*stack)->content))->special = 1;
	}
	else if (((t_stack *)((*stack)->content))->special)
		((t_stack *)((*stack)->content))->special = 0;
	else if ((*stack) && !(((t_stack *)((*stack)->content))->special))
	{
		push(stack, **token);
		((t_stack *)((*stack)->content))->special = 1;
	}
}

int			handle_ut_dollar_sign(t_list **stack, char **token, t_data *data,
									t_list *list)
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
		expand_dollar_sign(token, stack, data, list);
		return (1);
	}
}

int			ret_expand_ut(t_list **stack)
{
	if ((*stack) && ((t_stack *)((*stack)->content))->special)
	{
		ft_putstr_fd("error while expanding !\n", 2);
		return (0);
	}
	return (1);
}

int			expand_unquoted_token(t_list **stack, char **token, t_data *data,
									t_list *list)
{
	int		first_back_slash;

	(*token)--;
	pop(stack);
	first_back_slash = 0;
	while (**token)
	{
		if (**token != '$' && **token != '\\')
		{
			if (handle_ut_non_special(stack, token))
				break ;
		}
		else if (**token == '\\')
			handle_ut_back_slash(stack, token, &first_back_slash);
		else if (**token == '$')
		{
			if (handle_ut_dollar_sign(stack, token, data, list))
				continue ;
		}
		if (**token == '\0')
			break ;
		(*token)++;
	}
	return (ret_expand_ut(stack));
}

int			handle_dq_non_special(t_list **stack, char **token)
{
	if (**token == '\"')
	{
		if (*stack && ((t_stack *)((*stack)->content))->special)
		{
			pop(stack);
			push(stack, **token);
		}
		else
		{
			(*token)++;
			return (1);
		}
	}
	else
		push(stack, **token);
	return (0);
}
