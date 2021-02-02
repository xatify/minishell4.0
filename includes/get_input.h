/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:56:47 by keddib            #+#    #+#             */
/*   Updated: 2021/02/02 11:36:53 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_INPUT_H
# define GET_INPUT_H

/*
** get_input
*/

int				get_next_line(int fd, char **line);
void            free_data(t_data *data);

#endif
