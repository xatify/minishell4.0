/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:00:18 by keddib            #+#    #+#             */
/*   Updated: 2021/01/13 16:31:52 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_BINARY_H
# define FIND_BINARY_H

/*
** find binary path of non build-in commands
*/

char    *find_binary_file(t_data *data, char *cmd_name);
char    *get_bins_path(t_data *data);
char    *absolute_path(char *cmd, char *PATH);


#endif
