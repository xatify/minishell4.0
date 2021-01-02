/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:40:06 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/02 14:23:20 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int             token_id(char *token)
{
    int     i;
    char *operators[5] = {">", "<", ">>", "|", ";"};
    i = 0;
    while (i < 5)
    {
        if (!(ft_strcmp(operators[i], token)))
            return (i);
        i++;
    }
    
    return (WORD);
}

void            identify_all_tokens(t_token *tokens)
{
    t_token     *token;

    token = tokens;
    while (token)
    {
        token->id = token_id(token->tkn);
        token = token->next;
    }
}

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
    pop(stack);
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
                    pop(stack);
                    push(stack, *(*input_cmd)++);
                    return (1);
                }
            }
            break;
        }
    }
    return (0);
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
    t_token     *token = NULL;
    t_stack     *stack = NULL;
    char        *tkn;

    while (TRUE)
    {
        push(&stack, *input_cmd++);
        if (top_stack(&stack) == 0x27)
        {
            if (!special(stack))
            {
                if (!handle_single_quote(&stack, &input_cmd))
                {
                    ft_printf("error while tokenizing\n");
                    free_tokens(&token);
                    free_stack(&stack);
                    break;
                }
            }
            else
            {
                pop(&stack);
                pop(&stack);
                push(&stack, 0x27);
                continue;
            }
        }
        if (top_stack(&stack) == 0x22)
        {
            if (!special(stack))
            {
                if (!handle_double_quote(&stack, &input_cmd))
                {
                    ft_printf("error while tokenizing\n");
                    free_tokens(&token);
                    free_stack(&stack);
                    break;
                }
            }
            else
            {
                 pop(&stack);
                pop(&stack);
                push(&stack, 0x22);
                continue;
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
    }
    identify_all_tokens(token);
    return (token);
}
