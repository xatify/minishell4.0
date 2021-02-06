/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:26:39 by keddib            #+#    #+#             */
/*   Updated: 2021/02/06 15:27:00 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_to_std(int *save_std)
{
	dup2(save_std[0], STDIN);
	close(save_std[0]);
	dup2(save_std[1], STDOUT);
	close(save_std[1]);
}

void	copy_fds(int *fd1, int *fd2)
{
	fd1[0] = fd2[0];
	fd1[1] = fd2[1];
}

void	set_fds(int save_std[2], int tmp_fd[2])
{
	save_std[0] = dup(STDIN);
	save_std[1] = dup(STDOUT);
	copy_fds(tmp_fd, save_std);
}

int		simple_cmd_file_redirection(t_command *cmd, int *save_std, int *tmp_fd)
{
	int 	file_fd[2];

	file_fd[0] = -1;
	file_fd[1] = -1;
	copy_fds(tmp_fd, save_std);
	if (!redirect_std(cmd, file_fd))
	{
		close(save_std[0]);
		close(save_std[1]);
		return (0);
	}
	if (file_fd[0] >= 0)
		tmp_fd[0] = file_fd[0];
	if (file_fd[1] >= 0)
		tmp_fd[1] = file_fd[1];
	set_to_std(tmp_fd);
	return (1);
}

int		stream_error(int *tmp_fd, int *save_std, t_list *cmds)
{
	copy_fds(tmp_fd, save_std);
	cmds = cmds->next;
	return (0);
}
