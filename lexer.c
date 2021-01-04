/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:40:06 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/04 10:41:59 by abbouzid         ###   ########.fr       */
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

int            identify_all_tokens(t_token *tokens)
{
    t_token     *token;

    token = tokens;
    while (token)
    {
        token->id = token_id(token->tkn);
        if (token->id <= 2)
        {
            if (!token->next || token_id((token->next)->tkn) != WORD)
                return (0);
        }
        token = token->next;
    }
    return (1);
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
    while (**input_cmd && top_stack(stack) != 0x27)
        push(stack, *(*input_cmd)++);
    if (top_stack(stack) == 0x27 && (is_white_character(**input_cmd) || **input_cmd == '\0'))
    {
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
            printf("error while tokenizing\n");
            free_tokens(tokens);
            free_stack(stack);
            return (0);
        }
        return (1);
    }
    pop(stack);
    pop(stack);
    push(stack, quote);
    return (1);
}

t_token     *tokenizing(char *input_cmd)
{
    t_token     *token = NULL;
    t_stack     *stack = NULL;

    while (TRUE)
    {
        push(&stack, *input_cmd++);
        if (top_stack(&stack) == 0x27 || top_stack(&stack) == 0x22)
        {
            if (handle_quotes(&stack, &input_cmd, &token))
                continue;
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
        return (NULL);
    //remove_escape_character(token);
    if (identify_all_tokens(token))
        return (token);
    free_tokens(&token);
    printf("error while parsing !\n");
    return (NULL);
}
