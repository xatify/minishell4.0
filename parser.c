/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:27:29 by abbouzid          #+#    #+#             */
/*   Updated: 2020/12/23 11:39:10 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void                initialize_cmd(t_simple_command *command)
{
    ft_memset(command, 0, sizeof(t_simple_command));
}

void                del_token_head(t_token **tokens)
{
    t_token     *tmp;

    tmp = (*tokens)->next;
    free((*tokens)->tkn);
    free(*tokens);
    (*tokens) = tmp;
}

int            handle_direction(t_token **tokens, t_simple_command *command, int redirection)
{
    char        **stream;

    if (redirection == OUTPUT)
        stream = &(command->outfile);
    else if (redirection == INPUT)
        stream = &(command->INPUT);
    else
        strem = &(command->append_outfile);
    del_token_head(tokens);
    if ((*tokens) && (*tokens)->id >= WORD)
    {
        if ((*stream) != NULL)
            free((*stream));
        if (!((*stream) = ft_strdup((*tokens)->tkn)))
            return (0);
        del_token_head(tokens);
        return (1);
    }
    return (0);
}

int     handle_cmd_name(t_token **tokens, t_simple_command *command)
{
    del_token_head(tokens);
    if ((*tokens) && (*tokens)->id >= WORD)
    {
        if (!(command->cmd_name = ft_strdup((*tokens->tkn)))
            return (0);
        del_token_head(tokens);
        return  (1);    
    }
    return (0);
}

int     handle_argument(t_token **tokens, t_simple_command *command)
{
    
}

t_simple_command    *simple_command(t_token    **tokens)
{
    t_simple_command    *command;
    t_token             *tmp;
    int                 id;
    
    if (!(command = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    initialize_cmd(command);
    while (*tokens && (*tokens)->id != PIPE && (*tokens)->id != SEMICOLON)
    {
        id  = (*tokens)->id;
        if (id == OUTPUT || id  == INPUT || id == APPEND_OUT)
        {
            if (!handle_direction(tokens, command, id))
            {
                //free command;
                return (NULL);
            }
        }
        else if (command->cmd_name == NULL)
        {
            if (!handle_cmd_name(tokens, command))
            {
                //free command;
                return (NULL);
            }
        }
        else if(!handle_arguments(tokens, command))
        {
            //free command;
            return (NULL);
        }
    }
    return (command);
}

void            add_back_pipeline(t_pipeline **pipeline, t_token **token)
{
    
}
t_pipeline      parser(t_token     *tokens)
{
    t_pipeline     *pipeline;
    t_token        *token;
    
    pipeline = NULL;
    token = tokens;
    while (token && token->id != SEMICOLON)
    {
        
    }
}