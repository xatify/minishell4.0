/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:11:03 by keddib            #+#    #+#             */
/*   Updated: 2021/02/06 17:16:40 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

BOOL		is_single_quote_token(char *token)
{
	return ((token[0] == '\'')? TRUE: FALSE);
}

BOOL		is_double_quote_token(char *token)
{
	return ((token[0] == '"')? TRUE: FALSE);
}

void		expand_new_tokens(char *tkn, t_list **p_stack, t_list **new_args)
{
	int		i;
	char	**splits;

	splits = ft_split(tkn, ' ');
	i = 0;
	if (splits[0])
	{
		push_str_to_stack(p_stack, splits[0]);
		i++;
	}
	while (splits[i])
	{
		ft_lstadd_back(new_args, ft_lstnew(ft_strdup(splits[i])));
		i++;
	}
	free_argv(splits);
}

void		expand_token_list(t_list *list, t_env_var *env_var, t_list **p_stack)
{
	t_list		*new_args;
	t_list		*tmp;

	new_args = NULL;
	if (list)
	{
		expand_new_tokens(env_var->value, p_stack, &new_args);
		if (new_args != NULL)
		{
			tmp = list->next;
			list->next = new_args;
			ft_lstlast(new_args)->next = tmp;
		}

	}
	else
		push_str_to_stack(p_stack, env_var->value);
}

char		*handle_expansion(t_list **stack, int error)
{
	t_list		*tmp;
	char		*expansion;

	if (error)
	{
		ft_lstclear(stack, free);
		return (NULL);
	}
	tmp = NULL;
	if (*stack)
	{
		empty_stack(stack, &tmp);
		expansion = ft_strdup(((t_token *)(tmp->content))->tkn);
		ft_lstclear(&tmp, free_token);
		return (expansion);
	}
	return (NULL);
}
