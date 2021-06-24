/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:57:53 by keddib            #+#    #+#             */
/*   Updated: 2021/06/23 16:46:27 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SHELL_H
# define INIT_SHELL_H

/*
** initialise the shell
*/

void	start_shell(t_data *data, char **envp);
void	free_data(t_data *data);
void	new_input(t_data *data);

#endif
