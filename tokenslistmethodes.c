/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenslistmethodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:43:36 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/25 14:57:45 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void                del_token_head(t_token **tokens)
{
    t_token     *tmp;

    tmp = (*tokens)->next;
    free((*tokens)->tkn);
    free(*tokens);
    (*tokens) = tmp;
}

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

t_token *new_token(char **str)
{
    t_token     *token;
    
    if (!(token = (t_token *)malloc(sizeof(t_token))))
        return (NULL);
    token->tkn = (*str);
    token->next = NULL;
    return (token);
}

int            identify_all_tokens(t_token *tokens)
{
    t_token     *token;

    token = tokens;
    while (token)
    {
        token->id = token_id(token->tkn);
        if (token->id != WORD)
        {
            if (token->id == SEMICOLON && !token->next)
                return (1);
            if (!token->next)
                return (0);
            if ((token->id == SEMICOLON || token->id == PIPE) && token_id((token->next)->tkn) <= 2)
            {
                token = token->next;
                continue;
            }
            if (token_id((token->next)->tkn) != WORD)
                return (0);
        }
        token = token->next;
    }
    return (1);
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
