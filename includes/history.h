/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:03:19 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/19 13:46:41 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

void	add_history(t_list **hist_head, t_list **hist_index, char *command);
char	*browse_history_up(t_list **history_index);
char	*browse_history_down(t_list **history_index, int *up);
int		clear_line (t_data *data);
int		set_sig(char **holder, t_data *data);
void	history_up(char **holder, t_data *data);
void	history_down(char **holder, t_data *data, int *up);
void	delete_char(char **holder, t_data *data);
void	end_of_file(t_data *data, char *holder);
void	append_to_holder(char *buffer, char **holder, t_data *data);
void	return_input(t_data *data, char *holder);
char	*path_to_hist(void);
void	get_history_from_file(int fd, t_data *data);
void	build_history(t_data *data);
void	save_history(t_data *data);
void	history_tail(t_data *data);

#endif
