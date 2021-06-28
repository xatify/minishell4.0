/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:08:35 by keddib            #+#    #+#             */
/*   Updated: 2021/06/27 15:38:47 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_double_quotes(t_list **stack, char **token, t_data *data)
{
	while (TRUE)
	{
		if (**token != '$')
		{
			push(stack, **token);
			if (**token == '\"')
			{
				(*token)++;
				break ;
			}
		}
		else
		{
			(*token)++;
			expand_dollar_sign(token, stack, data);
			continue ;
		}
		(*token)++;
	}
}

void	expand_quotes(t_list **stack, char **token, t_data *data)
{
	if (top_stack(stack) == '\'')
	{
		while (**token != '\'')
			push(stack, *(*token)++);
		push(stack, *(*token)++);
	}
	else
		expand_double_quotes(stack, token, data);
}

void	expand_unquoted_token(t_list **stack, char **token, t_data *data)
{
	(*token)--;
	pop(stack);
	while (**token)
	{
		if (**token != '$')
		{
			if (**token == '\'' || **token == '\"')
				break ;
			push(stack, **token);
			(*token)++;
		}
		else
		{
			(*token)++;
			expand_dollar_sign(token, stack, data);
		}
		if (**token == '\0')
			break ;
	}
}

void	rmq(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			ft_strcpy(&(str[i]), &(str[i + 1]));
			while (str[i] && str[i] != quote)
				i++;
			ft_strcpy(&(str[i]), &(str[i + 1]));
		}
		else
			i++;
	}
}

t_list	*rm_quotes(t_list *tokens)
{
	t_list	*list;
	char	*str;
	t_list	*tmp;

	list = NULL;
	tmp = tokens;
	while (tokens)
	{
		str = ((t_token *)(tokens->content))->tkn;
		rmq(str);
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(str)));
		tokens = tokens->next;
	}
	ft_lstclear(&(tmp), free_token);
	return (list);
}
