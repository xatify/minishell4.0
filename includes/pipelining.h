/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelining.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:51:23 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/08 16:43:34 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINING_H
# define PIPELINING_H

/*
** pipeline stream
*/
void	set_to_std(int *save_std);
void	copy_fds(int *fd1, int *fd2);
void	set_fds(int save_std[2], int tmp_fd[2]);
int		simple_cmd_file_redirection(t_command *cmd, int *save_std, int *tmp_fd);
int		stream_error(int *tmp_fd, int *save_std, t_list *cmds);
int		pipeline_stream(t_command *cmd, int *save_std, int *tmp_fd,
		t_list *cmds);

#endif
