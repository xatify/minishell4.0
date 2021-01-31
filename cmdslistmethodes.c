/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdslistmethodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:17:15 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/30 09:32:40 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void                initialize_cmd(t_command *command)
{
    ft_memset(command, 0, sizeof(t_command));
    command->output_stream = -1;
}

void                free_command(t_command *command)
{
    if (!command)
        return;
    free_strlist(command->name_and_args);
    free_strlist(command->infiles);
    free_strlist(command->outfiles);
    free_strlist(command->append_outfiles);

    free(command);
}

t_command  *last_command(t_command *cmd)
{
    if (!cmd)
        return (NULL);
    if (!cmd->next)
        return (cmd);
    return (last_command(cmd->next));
}

void            add_back_command(t_command **cmd_head, t_command *command)
{
    if (!(*cmd_head))
    {
        *cmd_head = command;
    }
    else
        last_command((*cmd_head))->next = command;
}

t_command    *new_cmd(void)
{
    t_command    *cmd;

    if (!(cmd = (t_command *)malloc(sizeof(t_command))))
        return (NULL);
    initialize_cmd(cmd);
    return (cmd);
}