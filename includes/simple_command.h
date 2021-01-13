/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:48:49 by keddib            #+#    #+#             */
/*   Updated: 2021/01/13 09:49:32 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_COMMAND_H
# define SIMPLE_COMMAND_H

/*
** simple command linked list methodes
*/

void                initialize_cmd(t_simple_command *command);
void                free_command(t_simple_command *command);
t_simple_command  	*last_command(t_simple_command *cmd);
void            	add_back_command(t_simple_command **cmd_head, t_simple_command *command);
t_simple_command	*new_cmd(void);
void				show_command(t_simple_command *cmd);


#endif
