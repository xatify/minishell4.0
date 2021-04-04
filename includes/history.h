/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:03:19 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/04 19:05:04 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

void	add_history(t_list **hist_head, t_list **hist_index, char *command);
char	*browse_history_up(t_list **history_index);
char	*browse_history_down(t_list **history_index);
int		clear_line (t_data *data);

#endif
