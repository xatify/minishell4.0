/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brows_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:51:37 by keddib            #+#    #+#             */
/*   Updated: 2021/06/19 13:59:09 by abbouzid         ###   ########.fr       */
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

char	*browse_history_down(t_list **history_index, int *up)
{
	char	*tmp;

	if ((*history_index))
	{
		if (up && *up && (*history_index) && (*history_index)->previous)
		{
			(*up) = 0;
			(*history_index) = (*history_index)->previous;
			(*history_index) = (*history_index)->previous;
			tmp = (*history_index)->content;
		}
		else
		{
			tmp = (*history_index)->content;
			(*history_index) = (*history_index)->previous;
		}
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

int	set_sig(char **holder, t_data *data)
{
	int		brk;

	brk = 0;
	if (g_pid == -130 || g_pid == -131)
	{
		data->exit_status = -g_pid;
		g_pid = 0;
	}
	if (g_pid == -2)
		g_pid = 0;
	if (g_pid == -1)
	{
		ft_putstr_fd("\n", STDERR);
		g_pid = 0;
		data->exit_status = 1;
		free(*holder);
		*holder = ft_strdup("");
		brk = 1;
	}
	return (brk);
}
