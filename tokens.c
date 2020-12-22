/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:40:06 by abbouzid          #+#    #+#             */
/*   Updated: 2020/12/22 14:10:20 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token *new_token(char **str)
{
    t_token     *token;
    
    if (!(token = (t_token *)malloc(sizeof(t_token))))
        return (NULL);
    token->tkn = (*str);
    token->next = NULL;
    return (token);
}

t_token *last_token(t_token *tokens)
{
    if (!tokens)
        return (NULL);
    if (!tokens->next)
        return (tokens);
    return (last_token(tokens->next));
}

void    add_token(t_token **tokens, t_token *new_token)
{
    if (!(*tokens))
        (*tokens) = new_token;
    else
        last_token((*tokens))->next = new_token;
}

int     handle_single_quote(t_stack **stack, char **input_cmd)
{
    pop(stack);
    while (**input_cmd && top_stack(stack) != 0x27)
        push(stack, *(*input_cmd)++);
    if (top_stack(stack) == 0x27 && (is_white_character(**input_cmd) || **input_cmd == '\0'))
    {
        pop(stack);
        push(stack, *(*input_cmd)++);
        return (1);
    }
    else
        return (0);
}

int     special(t_stack *stack)
{
    t_stack *tmp;
    int     spcl;

    spcl = 0;
    tmp = stack->next;
    while (tmp->character == 0x5c)
        spcl++;
    return (spcl % 2)    
}


int     handle_double_quote(t_stack **stack, char **input_cmd)
{
    pop(stack);
    while(**input_cmd)
    {
        push(stack, *(*input_cmd)++);
        if (top_stack(stack) != '"')
           continue;
        else
        {
            if (special(stack))
            contiue;
    }
}
void     free_tokens(t_token **head)
{
    t_token  *tmp;

    if (*head == NULL)
        return;
    else
    {
        tmp = (*head)->next;
        free((*head)->tkn);
        free(*head);
        *head = NULL;
        free_tokens(&tmp);
    }  
}

t_token     *tokenizing(char *input_cmd)
{
    t_token     *token;
    t_stack     *stack;
    char        *tkn;

    stack = NULL;
    token = NULL;
    while (TRUE)
    {
        push(&stack, *input_cmd);
        if (top_stack(&stack) == 0x27)
        {
            input_cmd++;
            if (!handle_single_quote(&stack, &input_cmd))
            {
                ft_printf("error while tokenizing\n");
                free_tokens(&token);
                free_stack(&stack);
                break;
            }
        }
        if (top_stack(&stack) == 0x22)
        {
            input_cmd++;
            if (!handle_double_quote(&stack, &input_cmd))
            {
                ft_printf("error while tokenizing\n");
                free_tokens(&token);
                free_stack(&stack);
                break;
            }
        }
        if (top_stack(&stack) == ' ' || top_stack(&stack) == '\t')
        {
            pop(&stack);
            if (top_stack(&stack) != '\0' && stack != NULL)
            {
                tkn = empty_stack(&stack);
                add_token(&token, new_token(&tkn));
            }
        }
        else if (top_stack(&stack) == '\0')
        {
            if (stack != NULL)
            {
                pop(&stack);
                if (stack != NULL)
                {
                    tkn = empty_stack(&stack);
                    add_token(&token, new_token(&tkn));
                }
                break;
            }
        }
        input_cmd++;
    }
    return (token);
}
