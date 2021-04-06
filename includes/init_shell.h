/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:57:53 by keddib            #+#    #+#             */
/*   Updated: 2021/04/06 12:03:02 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SHELL_H
# define INIT_SHELL_H

/*
** initialise the shell
*/

t_data	*start_shell(int argc, char **argv, char **envp, char **holder);
void	show_prompt(t_data *data);
void	handl_signals_exit_status(t_data *data);
void	set_input_cmd(t_data *data, char **holder);
void	free_data(t_data *data);
void	new_input(t_data *data, char **holder);
void	at_exit(int a, t_data *data);
#endif
