/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:57:53 by keddib            #+#    #+#             */
/*   Updated: 2021/01/15 11:20:28 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTI_SHELL_H
# define INTI_SHELL_H

/*
** initialise the shell
*/

t_data	*start_shell(int argc, char **argv, char **envp);
void 	show_prompt(t_data *data);

#endif
