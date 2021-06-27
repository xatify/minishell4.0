/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:22:22 by keddib            #+#    #+#             */
/*   Updated: 2021/06/27 16:52:55 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_std_stream(int std, int fd)
{
	close(std);
	dup(fd);
	close(fd);
}

void	first_child(t_command *cmd, int *pipe_fds, int *file_fds)
{
	if (!redirect_std(cmd, file_fds))
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exit(1);
	}
	if (file_fds[0] != -1)
		set_std_stream(0, file_fds[0]);
	if (file_fds[1] != -1)
		set_std_stream(1, file_fds[1]);
	else
		set_std_stream(1, pipe_fds[1]);
	close(pipe_fds[0]);
}

void	middle_child(t_command *cmd, int *pipe_fds, int *file_fds, int in_tmp)
{
	if (!redirect_std(cmd, file_fds))
	{
		close(in_tmp);
		close(pipe_fds[1]);
		exit(1);
	}
	if (file_fds[0] != -1)
	{
		close(in_tmp);
		set_std_stream(0, file_fds[0]);
	}
	else
		set_std_stream(0, in_tmp);
	if (file_fds[1] != -1)
		set_std_stream(1, file_fds[1]);
	else
		set_std_stream(1, pipe_fds[1]);
}

void	last_child(t_command *cmd, int *file_fds, int in_tmp)
{
	if (!redirect_std(cmd, file_fds))
	{
		close(in_tmp);
		exit(1);
	}
	if (file_fds[0] != -1)
	{
		close(in_tmp);
		set_std_stream(0, file_fds[0]);
	}
	else
		set_std_stream(0, in_tmp);
	if (file_fds[1] != -1)
		set_std_stream(1, file_fds[1]);
}

void	piping_to_child(t_command *cmd, int *pipe_fd, t_list *cmds,
		int index_in_tmp[2])
{
	int		file_fds[2];

	ft_memset(file_fds, 255, 8);
	if (index_in_tmp[0] == 0)
		first_child(cmd, pipe_fd, file_fds);
	else if (cmds->next)
		middle_child(cmd, pipe_fd, file_fds, index_in_tmp[1]);
	else
		last_child(cmd, file_fds, index_in_tmp[1]);
	ft_lstclear(&(cmd->tmp_files), free_tmp_files);
}
