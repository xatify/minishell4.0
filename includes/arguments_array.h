/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_array.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:18:03 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/03 10:42:55 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_ARRAY_H
# define ARGUMENTS_ARRAY_H

/*
** building arguments array from the linked list
*/

char	**built_argv(t_command *cmd);
void	free_argv(char **argv);
int		args_num(char **args);

#endif
