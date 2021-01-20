/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:19:07 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/20 12:41:45 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int    redirect_stdout(t_simple_command *cmd)
{
    int     fd;
    int     ret;
    
    ret = -2;
    while (cmd->outfiles)
    {
        fd = open(cmd->outfiles->str, O_TRUNC | O_CREAT | O_RDWR, 0666);
        if (fd < 0)
            return (-1);
        if (!(cmd->outfiles->next))
        {
            if (cmd->output_stream == OUTPUT)
                ret = fd;
        }
        else
            close(fd);
        cmd->outfiles = cmd->outfiles->next;    
    }
    while (cmd->append_outfiles)
    {
        fd = open(cmd->append_outfiles->str, O_APPEND | O_CREAT | O_RDWR, 0666);
        if (fd < 0)
            return (-1);
        if (!(cmd->append_outfiles->next))
        {
            if (cmd->output_stream == APPEND_OUT)
                ret = fd;
        }
        else
            close(fd);
        cmd->append_outfiles = cmd->append_outfiles->next;   
    }
    return (ret);
}

int     redirect_stdin(t_simple_command *cmd)
{
    int fd;
    
    while(cmd->infiles)
    {
        fd = open(cmd->infiles->str, O_RDONLY);
        if (fd < 0)
        {
            ft_putstr_fd("no such file or directory: ", 2);
            ft_putstr_fd(cmd->infiles->str, 2);
            ft_putchar_fd('\n', 2);
            return (0);
        }
        if (!(cmd->infiles->next))
            return (fd);
        close(fd);
        cmd->infiles = cmd->infiles->next;
    }
    return (-2);
}