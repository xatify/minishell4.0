/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:25:23 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/20 12:26:15 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_REDIRECTION_H
# define OUTPUT_REDIRECTION_H

/*
** creating output files and redirecting to the right file
*/

int     redirect_stdout(t_simple_command *cmd);
int     redirect_stdin(t_simple_command *cmd);
#endif