/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:03:59 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/06 15:26:57 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		pipeline_stream(t_command *cmd, int *save_std, int *tmp_fd, t_list *cmds)
{
	int 	holder[2];
	int 	pipe_fd[2];

	holder[0] = -1;
	holder[1] = -1;
	if (!redirect_std(cmd, holder))
		return (stream_error(tmp_fd, save_std, cmds));
	if (holder[0] >= 0)
		tmp_fd[0] = holder[0];
	dup2(tmp_fd[0], STDIN);
	if (pipe(pipe_fd) < 0)
		return (stream_error(tmp_fd, save_std, cmds));
	copy_fds(tmp_fd, pipe_fd);
	if (holder[1] >= 0)
	{
		tmp_fd[1] = holder[1];
		close(pipe_fd[1]);
	}
	else if (!(cmds->next))
		tmp_fd[1] = save_std[1];
	dup2(tmp_fd[1], STDOUT);
	close(tmp_fd[1]);
	return (1);
}
