/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:02:33 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 13:12:51 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_from_stack(t_list **stack)
{
	int		len;
	char	*str;

	len = ft_lstsize(*stack);
	str = (char *)malloc(len + 1);
	if (!str)
		return (str);
	str[len] = '\0';
	while (--len >= 0)
		str[len] = pop(stack);
	return (str);
}

int	empty_stack(t_list **stack, t_list **tokens)
{
	int		len;
	char	*str;
	t_token	*tkn;

	len = ft_lstsize((*stack));
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
	while (--len >= 0)
		str[len] = pop(stack);
	tkn = new_token(&str);
	if (!tkn)
	{
		free(str);
		return (0);
	}
	ft_lstadd_back(tokens, ft_lstnew(tkn));
	return (1);
}

BOOL	is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (TRUE);
	return (FALSE);
}

void	is_metacharacter(t_list **stack)
{
	char	top;

	top = top_stack(stack);
	if (is_meta(top) && !special((*stack)))
		((t_stack *)((*stack)->content))->meta = 1;
}

void	push_str_to_stack(t_list **stack, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		push(stack, str[i]);
		i++;
	}
}
