/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:27:29 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/17 09:26:40 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

int            parse_redirection(t_token **tokens, t_simple_command *command, int redirection)
{
    t_strlist        **streams;

    if (redirection == OUTPUT)
        streams = &(command->outfiles);
    else if (redirection == INPUT)
        streams = &(command->infiles);
    else
        streams = &(command->append_outfiles);
    del_token_head(tokens);
    if ((*tokens) && (*tokens)->id >= WORD)
    {
        if (!add_strlist(streams, (*tokens)->tkn))
            return (0);
        del_token_head(tokens);
        return (1);
    }
    return (0);
}

int     parse_cmd_name(t_token **tokens, t_simple_command *command)
{
    if ((*tokens) && (*tokens)->id >= WORD)
    {
        if (!(command->cmd_name = ft_strdup((*tokens)->tkn)))
            return (0);
        del_token_head(tokens);
        return  (1);    
    }
    return (0);
}


int     parse_arguments(t_token **tokens, t_simple_command *command)
{
    if (!add_strlist((&command->arguments), (*tokens)->tkn))
        return (0);
    del_token_head(tokens);
    return (1);
}


t_simple_command    *parse_simple_command(t_token    **tokens)
{
    t_simple_command    *command;
    int                 id;
    int                 first_redirection;
    
    if (!(command = new_cmd()))
        return (NULL);
    first_redirection = 0;
    while (*tokens && (*tokens)->id != PIPE && (*tokens)->id != SEMICOLON)
    {
        id  = (*tokens)->id;
        if (id == OUTPUT || id  == INPUT || id == APPEND_OUT)
        {
            if (!parse_redirection(tokens, command, id))
            {
                free_command(command);
                return (NULL);
            }
            else if ((id == OUTPUT || id == APPEND_OUT) && !first_redirection)
            {
                first_redirection = 1;
                command->output_stream = id;
            }
        }
        else if (command->cmd_name == NULL)
        {
            if (!parse_cmd_name(tokens, command))
            {
                free_command(command);
                return (NULL);
            }
        }
        else if(!parse_arguments(tokens, command))
        {
            free_command(command);
            return (NULL);
        }
    }
    if (!command->cmd_name)
    {
        free_command(command);
        return (NULL);
    }
    return (command);
}


t_pipeline      *parse_pipe_line(t_token **tokens)
{
    t_pipeline          *pipeline;
    t_simple_command    *command;
    
    if (!(pipeline = new_pipe_line()))
        return (NULL);
    while (*tokens && (*tokens)->id != SEMICOLON)
    {
        if (!(command = parse_simple_command(tokens)))
        {
            free_pipeline(pipeline);
            return (NULL);
        }
        add_back_command(&pipeline->simple_cmd, command);
        if ((*tokens) && (*tokens)->id == PIPE)
        {
            del_token_head(tokens);
            continue;
        }
    }
    return (pipeline);
}


t_pipeline      *parser(char    *input_cmd)
{
    t_token        *tokens;
    t_pipeline     *pipeline_head;
    t_pipeline     *tmp;
    
    tokens = lexer(input_cmd);
    pipeline_head = NULL;
    while (tokens)
    {
        if (!(tmp = parse_pipe_line(&tokens)))
        {
            free_pipeline_list(pipeline_head);
            return (NULL);
        }
        add_back_pipeline(&pipeline_head, tmp);
        if (tokens && tokens->id == SEMICOLON)
        {
            del_token_head(&tokens);
            continue;
        }
    }
    return (pipeline_head);
}