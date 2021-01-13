/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:44:38 by keddib            #+#    #+#             */
/*   Updated: 2021/01/13 09:47:32 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRLIST_H
# define STRLIST_H

/*
** str linked list methodes
*/

t_strlist 			*new_strlist(char   *str);
t_strlist 			*last_strlist(t_strlist *strlist);
int     			add_strlist(t_strlist **strlist, char *str);
void                free_strlist(t_strlist *strlist);
void        		show_strlist(t_strlist *strlist);

#endif
