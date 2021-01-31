/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_array.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:18:03 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/30 08:34:49 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_ARRAY_H
# define ARGUMENTS_ARRAY_H

/*
** building arguments array from the linked list
*/

char    **built_argv(t_command *cmd);
void    free_argv(char **argv);
int     args_num(char **args);

#endif