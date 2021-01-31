/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelining.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:03:59 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/31 07:47:12 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    set_to_std(int *save_std)
{
    dup2(save_std[0], STDIN);
    dup2(save_std[1], STDOUT);
}

int     simple_cmd_file_redirection(t_command *cmd, int *save_std, int *tmp_fd)
{
    //set to default
    tmp_fd[1] = save_std[1];
    tmp_fd[0] = save_std[0];
    if (!redirect_stdin(cmd, &tmp_fd[0]) || !redirect_stdout(cmd, &tmp_fd[1]))
    {
        close(save_std[0]);
        close(save_std[1]);
        return (0);
    }
    set_to_std(tmp_fd);
    return (1);
}

int     pipeline_stream(t_command *cmd, int *save_std, int *tmp_fd)
{
    int     tmp;
    int     pipe_fd[2];

    if (!redirect_stdin(cmd, &tmp_fd[0]))
        return (0);
    dup2(tmp_fd[0], STDIN);
    if (pipe(pipe_fd) < 0)
        return (0);
    tmp_fd[0] = pipe_fd[0];
    tmp_fd[1] = pipe_fd[1];
    tmp = -1;
    if (!redirect_stdout(cmd, &tmp))
        return (0);
    if (tmp != -1)
    {
        tmp_fd[1] = tmp;
        close(pipe_fd[1]);
    }
    else if (!cmd->next)
        tmp_fd[1] = dup(save_std[1]);
    dup2(tmp_fd[1], STDOUT);
    close(tmp_fd[1]);
    return (1);
}
