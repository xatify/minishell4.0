/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:48:49 by keddib            #+#    #+#             */
/*   Updated: 2021/02/01 16:30:37 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_COMMAND_H
# define SIMPLE_COMMAND_H

/*
** simple command linked list methodes
*/

void                free_command(void *command);
t_command	        *new_cmd(void);


#endif
