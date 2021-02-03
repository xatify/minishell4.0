/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:03:59 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/03 10:59:05 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    set_to_std(int *save_std)
{
    dup2(save_std[0], STDIN);
    close(save_std[0]);
    dup2(save_std[1], STDOUT);
    close(save_std[1]);
}

void    copy_fds(int *fd1, int *fd2)
{
    fd1[0] = fd2[0];
    fd1[1] = fd2[1];
}

int     simple_cmd_file_redirection(t_command *cmd, int *save_std, int *tmp_fd)
{
    copy_fds(tmp_fd, save_std);
    if (!redirect_stdin(cmd, &tmp_fd[0]) || !redirect_stdout(cmd, &tmp_fd[1]))
    {
        close(save_std[0]);
        close(save_std[1]);
        return (0);
    }
    set_to_std(tmp_fd);
    return (1);
}

int    stream_error(int *tmp_fd, int *save_std, t_list *cmds)
{
    copy_fds(tmp_fd, save_std);
    cmds = cmds->next;
    return (0);
}

int     pipeline_stream(t_command *cmd, int *save_std, int *tmp_fd, t_list *cmds)
{
    int     tmp;
    int     pipe_fd[2];

    if (!redirect_stdin(cmd, &tmp_fd[0]))
        return (stream_error(tmp_fd, save_std, cmds));
    dup2(tmp_fd[0], STDIN);
    if (pipe(pipe_fd) < 0)
        return (stream_error(tmp_fd, save_std, cmds));
    copy_fds(tmp_fd, pipe_fd);
    tmp = -1;
    if (!redirect_stdout(cmd, &tmp))
        return (stream_error(tmp_fd, save_std, cmds));
    if (tmp != -1)
    {
        tmp_fd[1] = tmp;
        close(pipe_fd[1]);
    }
    else if (!(cmds->next))
        tmp_fd[1] = save_std[1];
    dup2(tmp_fd[1], STDOUT);
    close(tmp_fd[1]);
    return (1);
}
