/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:02:33 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/03 11:09:01 by abbouzid         ###   ########.fr       */
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
    new_element->next = NULL;
    return (new_element);
}


void	   push(t_stack **stack_head, char 	character)
{
	t_stack		*element;
    t_stack     *tmp;

    element = new_element(character);
    if (!element)
        return;
    if (!(*stack_head))
        (*stack_head) = element;
    else
    {
        tmp = (*stack_head);
        (*stack_head) = element;
        (*stack_head)->next = tmp;
    }
    is_metacharcter(stack_head);
}

char    pop(t_stack **stack_head)
{
    t_stack     *tmp;
    char        c;
    if ((*stack_head))
    {
        c = (*stack_head)->character;
        tmp = (*stack_head)->next;
        free((*stack_head));
        (*stack_head) = tmp;
        return (c);
    }
    return ('\0');
}

char    top_stack(t_stack **head)
{
    if (*head)
        return ((*head)->character);
    return ('\0');       
}

int     stack_len(t_stack **head)
{
    t_stack *tmp;
    int     i;

    i = 0;
    tmp = *head;
    while(tmp)
    {
        i++;
        tmp= tmp->next;
    }
    return (i);
}

void    free_stack(t_stack **stack)
{
    while (*stack)
        pop(stack);   
}

char    *empty_stack(t_stack **head)
{
    int     len;
    char    *str;

    if (!(*head))
        return (NULL);
    len = stack_len(head);
    if (!(str = (char *)malloc(len + 1)))
        return (NULL);
    str[len] = '\0';
    while (--len >= 0)
        str[len] = pop(head);
    return (str);   
}

void        is_metacharacter(t_stack **stack)
{
    char    top;

    top = top_stack(stack);
    if ((top == '|' || top == '>' || top == '<' || top == ';') && special((*stack)))
        (*stack)->meta = 1;
}