/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brows_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:51:37 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 11:52:55 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*browse_history_up(t_list **history_index)
{
	char	*tmp;

	if (*history_index)
	{
		tmp = (*history_index)->content;
		if ((*history_index)->next != NULL)
			(*history_index) = (*history_index)->next;
		return (tmp);
	}
	return (NULL);
}

char	*browse_history_down(t_list **history_index)
{
	char	*tmp;

	if ((*history_index))
	{
		tmp = (*history_index)->content;
		(*history_index) = (*history_index)->previous;
		return (tmp);
	}
	return (NULL);
}

void	build_history(t_data *data)
{
	int		fd;

	fd = open(HIST_FILE, O_RDONLY);
	if (fd >= 0)
	{
		get_history_from_file(fd, data);
		close(fd);
	}
}

void	history_tail(t_data *data)
{
	int		i;

	i = 0;
	data->history_index = data->history_head;
	while (i < HIST_SIZE && data->history_index)
	{
		if (!data->history_index->next)
			break ;
		data->history_index = data->history_index->next;
		i++;
	}
}
