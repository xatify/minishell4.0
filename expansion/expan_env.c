/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:10:21 by keddib            #+#    #+#             */
/*   Updated: 2021/06/27 16:26:28 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_env_var(t_list **tmp[2], t_list **vars)
{
	t_list		*var_name;
	t_env_var	*env_var;

	var_name = NULL;
	empty_stack(tmp[1], &var_name);
	if (var_name && *((t_token *)(var_name->content))->tkn)
	{
		env_var = search_var(vars, ((t_token *)(var_name->content))->tkn);
		if (env_var)
			push_str_to_stack(tmp[0], env_var->value);
		ft_lstclear(&var_name, free_token);
	}
}

void	expand_exit_status(t_list **p_stack, t_data *data, char **token)
{
	char	*value;

	(*token)++;
	value = ft_itoa(data->exit_status);
	push_str_to_stack(p_stack, value);
	free(value);
}

void	handle_expand_env_var(char **token, t_list **p_stack, t_data *data)
{
	t_list	*s_stack;
	t_list	**tmp[2];

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
	expand_env_var(tmp, &(data->env_vars));
}

void	expand_dollar_sign(char **token, t_list **p_stack, t_data *data)
{
	if (**token == '?')
		expand_exit_status(p_stack, data, token);
	else if (is_num(**token))
		(*token)++;
	else
		handle_expand_env_var(token, p_stack, data);
}

void	set_cmd_name(t_command *cmd)
{
	t_list		*tmp;
	char		*arg;
	t_list		*tmp2;

	tmp = cmd->name_and_args;
	while (tmp)
	{
		arg = tmp->content;
		if (arg && arg[0] == '\0')
		{
			tmp2 = tmp;
			free(tmp->content);
			free(tmp);
			tmp = tmp2->next;
		}
		else
			break ;
	}
	cmd->name_and_args = tmp;
}
