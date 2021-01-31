/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:48:49 by keddib            #+#    #+#             */
/*   Updated: 2021/01/30 08:34:49 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_COMMAND_H
# define SIMPLE_COMMAND_H

/*
** simple command linked list methodes
*/

void                initialize_cmd(t_command *command);
void                free_command(t_command *command);
t_command  	*last_command(t_command *cmd);
void            	add_back_command(t_command **cmd_head, t_command *command);
t_command	*new_cmd(void);
void				show_command(t_command *cmd);


#endif
