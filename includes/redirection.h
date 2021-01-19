/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:25:23 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/19 12:18:54 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_REDIRECTION_H
# define OUTPUT_REDIRECTION_H

/*
** creating output files and redirecting to the right file
*/

int     redirect_stdout(t_simple_command *cmd/*, t_data *data*/, int *outfile);
int     redirect_stdin(t_simple_command *cmd/*, t_data *data*/, int *infile);
#endif