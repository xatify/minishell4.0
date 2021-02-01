/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:02:33 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/01 10:21:20 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_stack     *new_element(char character)
{
    t_stack     *new_element;

    if (!(new_element = (t_stack *)malloc(sizeof(t_stack))))
        return (NULL);
    new_element->character = character;
    new_element->meta = 0;
    new_element->special = 0;
    return (new_element);
}


void	   push(t_list **stack, char 	character)
{
	t_stack		*stack_element;
    t_list      *node;

    stack_element = new_element(character);
    node = ft_lstnew(stack_element);
    ft_lstadd_back(stack, stack_element);
    is_metacharacter(stack);
}

char    pop(t_list **stack)
{
    t_list     *tmp;
    char        c;
    
    if (*stack)
    {
        c = ((t_stack *)((*stack)->content))->character;
        tmp = (*stack)->next;
        free((*stack)->content);
        free((*stack));
        (*stack) = tmp;
        return (c);
    }
    return ('\0');
}

char    top_stack(t_list **stack)
{
    if (*stack)
        return (((t_stack *)(*stack)->content)->character);
    return ('\0');
}

int    empty_stack(t_list **stack, t_list **tokens)
{
    int     len;
    char    *str;
    t_token *tkn;

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

bool    is_meta(char c)
{
    if (c == '|' || c == '>' || c == '<' || c == ';')
        return(TRUE);
    return (FALSE);
}

void        is_metacharacter(t_stack **stack)
{
    char    top;

    top = top_stack(stack);
    if (is_meta(top) && !special((*stack)))
        (*stack)->meta = 1;
}

void    push_str_to_stack(t_stack **stack, char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        push(stack, str[i]);
        i++;
    }
}