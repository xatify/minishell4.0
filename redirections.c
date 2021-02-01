/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:19:07 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/01 15:47:23 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int    redirect_stdout(t_command *cmd, int *fdout)
{
    int     fd;
    t_list  *tmp;

    tmp = cmd->outfiles;
    while (tmp)
    {
        fd = open(tmp->content, O_TRUNC | O_CREAT | O_RDWR, 0666);
        if (fd < 0)
            return (0);
        if (!(tmp->next))
        {
            if (cmd->output_stream == OUTPUT)
            {
                *fdout = fd;
                break;
            }
        }
        else
            close(fd);
        tmp = tmp->next;
    }
    tmp = cmd->append_outfiles;
    while (tmp)
    {
        fd = open(tmp->content, O_APPEND | O_CREAT | O_RDWR, 0666);
        if (fd < 0)
            return (0);
        if (!(tmp->next))
        {
            if (cmd->output_stream == APPEND_OUT)
            {
                *fdout = fd;
                break;
            }
        }
        else
            close(fd);
        tmp = tmp->next;
    }
    return (1);
}

int     redirect_stdin(t_command *cmd, int *fdin)
{
    int fd;
    t_list *tmp;

    tmp = cmd->infiles;
    
    while(tmp)
    {
        fd = open(tmp->content, O_RDONLY);
        if (fd < 0)
        {
            ft_putstr_fd("no such file or directory: ", 2);
            ft_putstr_fd(tmp->content, 2);
            ft_putchar_fd('\n', 2);
            return (0);
        }
        if (!(tmp->next))
        {
            *fdin = fd;
            return (1);
        }
        close(fd);
        tmp = tmp->next;
    }
    return (1);
}
