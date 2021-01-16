/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:10:48 by keddib            #+#    #+#             */
/*   Updated: 2021/01/16 09:15:54 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

/*
** variables manipulation
*/

char				*remove_quotes(char *value);
char 				**get_all_vars(t_env_vars *env_vars, t_strlist *unset_vars);

#endif
