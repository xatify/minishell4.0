/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:03:19 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/05 17:19:02 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

void	add_history(t_list **hist_head, t_list **hist_index, char *command);
char	*browse_history_up(t_list **history_index);
char	*browse_history_down(t_list **history_index);
int		clear_line (t_data *data);
int		set_sig(char **holder, t_data  *data);
void	history_up(char **holder, t_data *data);
void	history_down(char **holder, t_data *data);
void	delete_char(char **holder, t_data *data);
void	end_of_file(t_data *data, char *holder);
void	append_to_holder(char *buffer, char **holder, t_data *data);
void	return_input(t_data *data, char *holder);

#endif
