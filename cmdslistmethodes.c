/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdslistmethodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:17:15 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/01 10:04:16 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_command    *new_cmd(void)
{
    t_command    *cmd;

    if (!(cmd = (t_command *)malloc(sizeof(t_command))))
        return (NULL);
    ft_memset(cmd, 0, sizeof(t_command));
    cmd->output_stream = -1;
    return (cmd);
}

void                free_command(t_command *command)
{
    if (!command)
        return;
    ft_lstclear(command->name_and_args, free);
    ft_lstclear(command->infiles, free);
    ft_lstclear(command->outfiles, free);
    ft_lstclear(command->append_outfiles, free);
    free(command);
}