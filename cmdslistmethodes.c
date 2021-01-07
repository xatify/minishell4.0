/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdslistmethodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:17:15 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/07 12:02:45 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void                initialize_cmd(t_simple_command *command)
{
    ft_memset(command, 0, sizeof(t_simple_command));
}

void                free_command(t_simple_command *command)
{
    if (!command)
        return;
    if (command->cmd_name)
        free(command->cmd_name);
    free_strlist(command->infiles);
    free_strlist(command->outfiles);
    free_strlist(command->outfiles);
    free_strlist(command->arguments);
    free(command);
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

t_simple_command    *new_cmd(void)
{
    t_simple_command    *cmd;
    
    if (!(cmd = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    initialize_cmd(cmd);
    return (cmd);
}

void            show_command(t_simple_command *cmd)
{
    if (cmd)
    {
        ft_printf("cmd_name : %s\t", cmd->cmd_name);
        if (cmd->arguments)
        {
            ft_printf("args : ");
            show_strlist(cmd->arguments);
        }
        if (cmd->outfiles)
        {
            ft_printf("> ");
            show_strlist(cmd->outfiles);
        }
        if (cmd->infiles)
        {
            ft_printf("< ");
            show_strlist(cmd->infiles);
        }
        if (cmd->append_outfiles)
        {
            ft_printf("<< ");
            show_strlist(cmd->append_outfiles);
        }
        if (cmd->next)
            ft_printf(" | ");
        show_command(cmd->next);
    }
}