/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:25:23 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 12:16:46 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

/*
** creating output files and redirecting to the right file
*/

t_redirection	*new_redirection(char *file, int type, t_command *cmd);
void			free_redirections(void *redirection);
void            free_tmp_files(void *tmp_file);
int				open_file(t_redirection *redirection);
void			set_streaming_fds(int *tmp_fd, int fd, int redirection_type);
int				redirect_std(t_command *cmd, int *tmp_fd);
int				simple_cmd_streaming(t_command *cmd, int *tmp_fds);

#endif
