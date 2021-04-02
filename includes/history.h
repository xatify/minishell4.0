/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:03:19 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/02 19:37:55 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

void	add_history(t_list **history, t_list *new);
char	*browse_history_up(t_list *history_index);
char	*brows_history_down(t_list *history_index);

#endif
