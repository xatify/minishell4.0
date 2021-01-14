/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:40:06 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/14 10:51:28 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int     handle_single_quote(t_stack **stack, char **input_cmd)
{
    while (**input_cmd)
    {
        push(stack, *(*input_cmd)++);
        if (top_stack(stack) != 0x27)
            continue;
        break;
    }
    if (top_stack(stack) == 0x27)
    {
        if (is_white_character((**input_cmd)) || is_meta(**input_cmd) || !(**input_cmd))
        {
            push(stack, *(*input_cmd));
            return (1);
        }
    }
    return (0);
}

int     special(t_stack *stack)
{
    t_stack *tmp;
    int     spcl;

    spcl = 0;
    tmp = stack->next;
    while (tmp)
    {
        if (tmp->character == 0x5c)
        {
            spcl++;
            tmp = tmp->next;
        }
        else
            break;
    }
    return (spcl % 2);
}


int     handle_double_quote(t_stack **stack, char **input_cmd)
{
    while(**input_cmd)
    {
        push(stack, *(*input_cmd)++);
        if (top_stack(stack) != '"')
           continue;
        else
        {
            if (special(*stack))
                continue;
            else
            {
                if (is_white_character(**input_cmd) || **input_cmd == '\0')
                {
                    push(stack, *(*input_cmd)++);
                    return (1);
                }
            }
            break;
        }
    }
    return (0);
}

int     handle_metacharacter(t_stack **stack, t_token **tokens, char **input_cmd)
{
    char        top;
    int         append;

    append = 0;
    top = top_stack(stack);
    pop(stack);
    if ((*stack))
    {
        if (!empty_stack(stack, tokens))
            return (0);
    }
    push(stack, top);
    if (top == '>' && **input_cmd == '>')
    {
        push(stack, *(*input_cmd)++);
        append = 1;
    }
    else if (is_meta(**input_cmd))
    {
        free_stack(stack);
        free_tokens(tokens);
        return (0);
    }
    if (!empty_stack(stack, tokens))
        return (0);
    pop(stack);
    if (append)
        pop(stack);
    return (1);
}

int       handle_quotes(t_stack **stack, char **input_cmd, t_token **tokens)
{
    char    quote;
    int     error;

    error = 0;
    quote = top_stack(stack);
    if (!special((*stack)))
    {
        if (quote == 0x27) // single_quote
        {
            if (!handle_single_quote(stack, input_cmd))
                error = 1;
        }
        else
        {
            if (!handle_double_quote(stack, input_cmd))
                error = 1;
        }
        if (error)
        {
            ft_putstr_fd("error while tokenizing\n", 1);
            free_tokens(tokens);
            free_stack(stack);
            return (0);
        }
        return (1);
    }
    return (1);
}

t_token     *lexer(char *input_cmd)
{
    t_token     *token = NULL;
    t_stack     *stack = NULL;

    if (*input_cmd == '\0')
        return (0);
    while (TRUE)
    {
        push(&stack, *input_cmd++);
        if (top_stack(&stack) == 0x27 || top_stack(&stack) == 0x22)
        {
            if (!handle_quotes(&stack, &input_cmd, &token))
                break;
        }
        if (top_stack(&stack) == ' ' || top_stack(&stack) == '\t')
        {
            pop(&stack);
            if (top_stack(&stack) != '\0' && stack != NULL)
            {
                if (empty_stack(&stack, &token))
                    continue;
                break;
            }
        }
        if (stack && stack->meta)
        {
            if (!handle_metacharacter(&stack, &token, &input_cmd))
                break;
        }
        else if (top_stack(&stack) == '\0')
        {
            if (stack != NULL)
            {
                pop(&stack);
                if (stack != NULL)
                    empty_stack(&stack, &token);
                break;
            }
        }
    }
    if (!token)
    {
        ft_putstr_fd("error while parsing !\n", 1);
        return (NULL);
    }
    if (identify_all_tokens(token))
        return (token);
    free_tokens(&token);
    ft_putstr_fd("error while parsing !\n", 1);
    return (NULL);
}
