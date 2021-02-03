/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelining.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:51:23 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/03 09:45:35 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINING_H
# define PIPELINING_H

/*
** pipeline stream
*/

void    set_to_std(int *save_std);
int     simple_cmd_file_redirection(t_command *cmd, int *save_std, int *tmp_fd);
int     pipeline_stream(t_command *cmd, int *save_std, int *tmp_fd, t_list *next_cmd);

#endif