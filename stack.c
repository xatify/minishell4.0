/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:02:33 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/08 09:20:36 by abbouzid         ###   ########.fr       */
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
    is_metacharacter(stack_head);
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

int    empty_stack(t_stack **head, t_token **tokens)
{
    int     len;
    char    *str;

    len = stack_len(head);
    if (!(str = (char *)malloc(len + 1)))
    {
        free_tokens(tokens);
        return (0);
    }
    str[len] = '\0';
    while (--len >= 0)
        str[len] = pop(head);
    add_token(tokens, new_token(&str));
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