/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:10:21 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 18:54:53 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_env_var(t_list **tmp[2], t_list **vars,
							t_list *list, char **token)
{
	t_list		*var_name;
	t_env_var	*env_var;

	var_name = NULL;
	empty_stack(tmp[1], &var_name);
	if (var_name && *((t_token *)(var_name->content))->tkn)
	{
		env_var = search_var(vars, ((t_token *)(var_name->content))->tkn);
		if (env_var)
			expand_token_list(list, env_var, tmp[0], token);
		ft_lstclear(&var_name, free_token);
	}
}

void	expand_exit_status(t_list **p_stack, t_data *data, char **token)
{
	(*token)++;
	push_str_to_stack(p_stack, ft_itoa(data->exit_status));
}

void	handle_expand_env_var(char **token, t_list **p_stack, t_data *data,
									t_list *list)
{
	t_list	*s_stack;
	t_list 	**tmp[2];

	s_stack = NULL;
	if (!(is_underscore(**token) || is_alpha(**token)))
	{
		push(p_stack, '$');
		return ;
	}
	while (**token)
	{
		if (is_alpha(**token) || is_num(**token) || is_underscore(**token))
		{
			push(&s_stack, **token);
			(*token)++;
		}
		else
			break ;
	}
	tmp[0] = p_stack;
	tmp[1] = &s_stack;
	expand_env_var(tmp, &(data->env_vars), list, token);
}

void	expand_dollar_sign(char **token, t_list **p_stack, t_data *data,
								t_list *list)
{
	t_list	*s_stack;

	s_stack = NULL;
	if (**token == '?')
		expand_exit_status(p_stack, data, token);
	else if (is_num(**token))
		(*token)++;
	else
		handle_expand_env_var(token, p_stack, data, list);
}

int	handle_ut_non_special(t_list **stack, char **token)
{
	if (**token == '\"' || **token == '\'')
	{
		if (*stack && ((t_stack *)((*stack)->content))->special)
		{
			pop(stack);
			push(stack, **token);
			return (0);
		}
		else
			return (1);
	}
	else
	{
		if (*stack && ((t_stack *)((*stack)->content))->special)
			pop(stack);
		push(stack, **token);
	}
	return (0);
}
