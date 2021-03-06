/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:56:47 by keddib            #+#    #+#             */
/*   Updated: 2021/02/03 10:49:13 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_INPUT_H
# define GET_INPUT_H

/*
** get_input
*/

int				get_next_line(int fd, char **line);
void			free_data(t_data *data);

#endif
