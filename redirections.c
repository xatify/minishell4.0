/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:19:07 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/17 10:35:39 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    redirect_stdout(t_simple_command *cmd)
{
    int     fd;

    while (cmd->outfiles)
    {
        fd = open(cmd->outfiles->str, O_TRUNC | O_CREAT | O_RDWR, 0666);
        if (!(cmd->outfiles->next))
        {
            if (cmd->output_stream == OUTPUT)
                dup2(fd, STDOUT);
        }
        close(fd);
        cmd->outfiles = cmd->outfiles->next;    
    }
    while (cmd->append_outfiles)
    {
        fd = open(cmd->append_outfiles->str, O_APPEND | O_CREAT | O_RDWR, 0666);
        if (!(cmd->append_outfiles->next))
        {
            if (cmd->output_stream == APPEND_OUT)
                dup2(fd, STDOUT);
        }
        close(fd);
        cmd->append_outfiles = cmd->append_outfiles->next;   
    }
}