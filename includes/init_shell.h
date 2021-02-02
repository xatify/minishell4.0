/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:57:53 by keddib            #+#    #+#             */
/*   Updated: 2021/02/02 16:15:49 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTI_SHELL_H
# define INTI_SHELL_H

/*
** initialise the shell
*/

t_data	*start_shell(int argc, char **argv, char **envp);
void 	show_prompt(t_data *data);
void    new_input(t_data *data, char **holder);

#endif
