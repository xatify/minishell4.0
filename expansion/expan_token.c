/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:11:03 by keddib            #+#    #+#             */
/*   Updated: 2021/03/29 18:53:31 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

BOOL		is_single_quote_token(char *token)
{
	return ((token[0] == '\'') ? TRUE : FALSE);
}

BOOL		is_double_quote_token(char *token)
{
	return ((token[0] == '"') ? TRUE : FALSE);
}

void		expand_new_tokens(char *tkn, t_list **p_stack, t_list **new_args)
{
	int		i;
	char	**splits;

	splits = ft_split(tkn, ' ');
	i = 0;
	if (splits[0] && (tkn[0] != ' ' || *p_stack == NULL))
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

void		expand_token_list(t_list *list, t_env_var *env_var,
								t_list **p_stack, char **token)
{
	t_list		*new_args;
	t_list		*tmp;
	t_list		*tmp1;
	char		*str;

	new_args = NULL;
	if (list)
	{
		expand_new_tokens(env_var->value, p_stack, &new_args);
		if (new_args != NULL)
		{
			tmp = list->next;
			list->next = new_args;
			if (**token == '\0')
				ft_lstlast(new_args)->next = tmp;
			else
			{
				if ((env_var->value)[ft_strlen(env_var->value) - 1] != ' ')
				{
					str = ft_strjoin(ft_lstlast(new_args)->content, *token);
					free(ft_lstlast(new_args)->content);
					ft_lstlast(new_args)->content = str;
				}
				else
				{
					tmp1 = ft_lstnew(ft_strdup(*token));
					ft_lstlast(new_args)->next = tmp1;
					tmp1->next = tmp;
				}
				**token = '\0';
			}
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
