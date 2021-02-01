/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenslistmethodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:43:36 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/01 10:17:55 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void                del_token_head(t_list **tokens)
{
    t_token     *tmp;

    tmp = (*tokens)->next;
    ft_lstdelone((*tokens), free_token);
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

int            identify_all_tokens(t_list *tokens)
{
    t_token     *token;
    
    while (tokens)
    {
        token = (t_token *)(tokens->content);
        token->id = token_id(token->tkn);
        if (token->id != WORD)
        {
            if (token->id == SEMICOLON && !(tokens->next))
                return (1);
            if (!(tokens->next))
                return (0);
            if ((token->id == SEMICOLON || token->id == PIPE) &&
                token_id(((t_token *)((tokens->next)->content))->tkn) <= 2)
            {
                tokens = tokens->next;
                continue;
            }
            if (token_id(((t_token *)((tokens->next)->content))->tkn) != WORD)
                return (0);
        }
        tokens = tokens->next;
    }
    return (1);
}

void    free_token(t_token *token)
{
    free(token->tkn);
    free(token);
}
