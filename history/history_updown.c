/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_updown.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:53:16 by keddib            #+#    #+#             */
/*   Updated: 2021/06/19 13:49:13 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	history_up(char **holder, t_data *data)
{
	char	*tmp;

	tmp = browse_history_up(&(data->history_index));
	if (data->history_index == NULL)
		data->history_index = data->history_head;
	if (data->history_head && data->history_head->next == NULL)
	{
		free(*holder);
		*holder = ft_strdup(data->history_head->content);
		clear_line(data);
		ft_putstr_fd(*holder, STDERR);
	}
	else if (tmp)
	{
		free(*holder);
		*holder = ft_strdup(tmp);
		clear_line(data);
		ft_putstr_fd(*holder, STDERR);
	}
}

void	history_down(char **holder, t_data *data, int *up)
{
	char	*tmp;

	tmp = browse_history_down(&(data->history_index), up);
	free(*holder);
	*holder = ft_strdup("");
	if (tmp)
		*holder = ft_strdup(tmp);
	clear_line(data);
	if (tmp)
		ft_putstr_fd(*holder, STDERR);
}
