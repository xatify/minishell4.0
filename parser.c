/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:27:29 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/03 16:10:53 by abbouzid         ###   ########.fr       */
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

int            handle_redirection(t_token **tokens, t_simple_command *command, int redirection)
{
    char        **stream;

    if (redirection == OUTPUT)
        stream = &(command->outfile);
    else if (redirection == INPUT)
        stream = &(command->infile);
    else
        stream = &(command->append_outfile);
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
    if ((*tokens) && (*tokens)->id >= WORD)
    {
        if (!(command->cmd_name = ft_strdup((*tokens)->tkn)))
            return (0);
        del_token_head(tokens);
        return  (1);    
    }
    return (0);
}

t_arguments *new_arg(char   *arg)
{
    t_arguments *args;
    
    if (!(args = (t_arguments *)malloc(sizeof(t_arguments))))
        return (NULL);
    if (!(args->arg = ft_strdup(arg)))
    {
        free(args);
        return (NULL);
    }
    args->next = NULL;
    return (args);
}

t_arguments *last_args(t_arguments *args)
{
    if (!(args))
        return (args);
    if (!(args->next))
        return (args);
    return (last_args(args->next));
}

int     add_arg(t_arguments **args, char *arg)
{
    t_arguments *tmp;
    
    if (!(tmp = new_arg(arg)))
        return (0);
    if (!(*args))
        (*args) = tmp;
    else
        (last_args((*args)))->next = tmp;
    return (1);
}

int     handle_argument(t_token **tokens, t_simple_command *command)
{
    if (!add_arg((&command->arguments), (*tokens)->tkn))
        return (0);
    del_token_head(tokens);
    return (1);
}

void                free_arguments(t_arguments *arguments)
{
    t_arguments *tmp;

    if (!arguments)
        return;
    tmp = arguments->next;
    free(arguments->arg);
    free(arguments);
    free_arguments(tmp);
}

void                free_command(t_simple_command *command)
{
    if (!command)
        return;
    if (command->cmd_name)
        free(command->cmd_name);
    if (command->infile)
        free(command->infile);
    if (command->outfile)
        free(command->outfile);
    if (command->append_outfile)
        free(command->append_outfile);
    free_arguments(command->arguments);
    free(command);
}

t_simple_command    *simple_command(t_token    **tokens)
{
    t_simple_command    *command;
    int                 id;
    
    if (!(command = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    initialize_cmd(command);
    while (*tokens && (*tokens)->id != PIPE && (*tokens)->id != SEMICOLON)
    {
        id  = (*tokens)->id;
        if (id == OUTPUT || id  == INPUT || id == APPEND_OUT)
        {
            if (!handle_redirection(tokens, command, id))
            {
                free_command(command);
                return (NULL);
            }
        }
        else if (command->cmd_name == NULL)
        {
            if (!handle_cmd_name(tokens, command))
            {
                free_command(command);
                return (NULL);
            }
        }
        else if(!handle_argument(tokens, command))
        {
            free_command(command);
            return (NULL);
        }
    }
    return (command);
}

t_simple_command  *last_command(t_simple_command *cmd)
{
    if (!cmd)
        return (NULL);
    if (!cmd->next)
        return (cmd);
    return (last_command(cmd->next));
}

void            add_back_command(t_simple_command **cmd_head, t_simple_command *command)
{
    if (!(*cmd_head))
        *cmd_head = command;
    else
        last_command((*cmd_head))->next = command;
}

void        free_pipeline(t_pipeline *pipeline)
{
    t_simple_command *tmp;
    
    if (!(pipeline))
        return;
    while (pipeline->simple_cmd)
    {
        tmp = pipeline->simple_cmd;
        pipeline->simple_cmd = tmp->next;
        free_command(tmp);
    }
    free(pipeline);
}

t_pipeline      *new_pipe_line(t_token **tokens)
{
    t_pipeline          *pipeline;
    t_simple_command    *command;
    
    if (!(pipeline = (t_pipeline *)malloc(sizeof(t_pipeline))))
        return (NULL);
    ft_memset(pipeline, 0, sizeof(t_pipeline));
    while (*tokens && (*tokens)->id != SEMICOLON)
    {
        if (!(command = simple_command(tokens)))
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

void        free_pipeline_list(t_pipeline *pipeline_head)
{
    t_pipeline  *tmp;
    
    while (pipeline_head)
    {
        tmp = pipeline_head->next;
        free_pipeline(pipeline_head);
        pipeline_head = tmp;
    }
}

t_pipeline      *last_pipeline(t_pipeline *pipeline)
{
    if (!pipeline)
        return (NULL);       
    if (!pipeline->next)
        return (pipeline);
    return (last_pipeline(pipeline->next));
}

void            add_back_pipeline(t_pipeline **pipe_head, t_pipeline *pipeline)
{
    if (!(*pipe_head))
        (*pipe_head) = pipeline;
    else
        last_pipeline((*pipe_head))->next = pipeline;
}

t_pipeline      *parser(t_token     **tokens)
{
    t_pipeline     *pipeline_head;
    t_pipeline     *tmp;
    
    pipeline_head = NULL;
    while ((*tokens))
    {
        if (!(tmp = new_pipe_line(tokens)))
        {
            free_pipeline_list(pipeline_head);
            return (NULL);
        }
        add_back_pipeline(&pipeline_head, tmp);
        if ((*tokens) && (*tokens)->id == SEMICOLON)
        {
            del_token_head(tokens);
            continue;
        }
    }
    return (pipeline_head);
}

void        show_parse_tree(t_pipeline *parse_tree)
{
    t_simple_command    *command;
    t_pipeline          *tmp;

    tmp = parse_tree;
    while (tmp)
    {
        command = tmp->simple_cmd;
        while (command)
        {
            printf("cmd_namd = %s\t", command->cmd_name);
            if (command->infile)
                printf("< %s\t", command->infile);
            if (command->outfile)
                printf("> %s\t", command->outfile);
            if (command->append_outfile)
                printf(">> %s\t", command->append_outfile);
            if (command->arguments)
            {
                printf("args : \t");
                while (command->arguments)
                {
                    printf("%s\t", (command->arguments)->arg);
                    command->arguments = (command->arguments)->next;
                }
            }
            if (command->next)
                printf("|\t");
            command = command->next;
        }
        if (tmp->next)
            printf(";\t");
        tmp = tmp->next;
    }
    printf("\n");
}

void    free_parse_tree(t_pipeline *parse_tree)
{   
    if (parse_tree)
    {
        free_pipeline_list(parse_tree->next);
        free_pipeline_list(parse_tree);
    }
}