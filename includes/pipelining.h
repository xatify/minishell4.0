/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelining.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:51:23 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/26 09:53:37 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINING_H
# define PIPELINING_H

/*
** pipeline stream
*/

void    set_to_std(int *save_std);
int     simple_cmd_file_redirection(t_simple_command *cmd, int *save_std, int *tmp_fd);
int     pipeline_stream(t_simple_command *cmd, int *save_std, int *tmp_fd);

#endif