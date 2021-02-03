/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:10:48 by keddib            #+#    #+#             */
/*   Updated: 2021/02/03 11:16:47 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

/*
** variables manipulation
*/

char				*remove_quotes(char *value);
int					get_vars_len(t_list *env_vars, t_list *unset_vars);
char				**get_all_vars(t_list *env_vars, t_list *unset_vars);

#endif
