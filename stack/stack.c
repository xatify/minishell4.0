/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:02:33 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/08 17:56:34 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			empty_stack(t_list **stack, t_list **tokens)
{
	int		len;
	char	*str;
	t_token	*tkn;

	len = ft_lstsize((*stack));
	if (!(str = (char *)malloc(len + 1)))
		return (0);
	str[len] = '\0';
	while (--len >= 0)
		str[len] = pop(stack);
	if (!(tkn = new_token(&str)))
	{
		free(str);
		return (0);
	}
	ft_lstadd_back(tokens, ft_lstnew(tkn));
	return (1);
}

BOOL		is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (TRUE);
	return (FALSE);
}

void		is_metacharacter(t_list **stack)
{
	char	top;

	top = top_stack(stack);
	if (is_meta(top) && !special((*stack)))
		((t_stack *)((*stack)->content))->meta = 1;
}

void		push_str_to_stack(t_list **stack, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		push(stack, str[i]);
		i++;
	}
}
