/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:25:23 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/05 11:08:44 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_REDIRECTION_H
# define OUTPUT_REDIRECTION_H

/*
** creating output files and redirecting to the right file
*/

t_redirection 	*new_redirection(char *file, int type);
void			free_redirections(void *redirection);
int 			open_file(t_redirection *redirection);
void			set_streaming_fds(int *tmp_fd, int fd, int redirection_type);
int     		redirect_std(t_command *cmd, int *tmp_fd);
#endif
