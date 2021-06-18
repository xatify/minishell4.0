/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:08:34 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 18:33:26 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_history(t_list **hist_head, t_list **hist_index, char *command)
{
	t_list		*new;

	new = NULL;
	if (*command)
	{
		if (((*hist_head) && ft_strcmp((*hist_head)->content, command))
			|| !(*hist_head))
			new = ft_lstnew(ft_strdup(command));
		if (new)
		{
			if (!(*hist_head))
				*hist_head = new;
			else
			{
				new->next = *hist_head;
				(*hist_head)->previous = new;
				*hist_head = new;
			}
			*hist_index = *hist_head;
		}
	}
}

int	clear_line(t_data *data)
{
	tputs(data->termc->clear_line, 1, putchar_2);
	tputs(data->termc->cariage_return, 1, putchar_2);
	ft_putstr_fd(PROMPT, STDERR);
	return (1);
}

void	get_history(int *hist_count, t_list **hist_tail, t_data *data,
					char *line)
{
	*hist_count += 1;
	add_history(&data->history_head, &data->history_index, line);
	if (*hist_count == 1)
		hist_tail = &data->history_head;
	if (*hist_count > HIST_SIZE)
	{
		hist_tail = &(*hist_tail)->previous;
		free((*hist_tail)->next->content);
		free((*hist_tail)->next);
		(*hist_tail)->next = NULL;
	}
}

void	get_history_from_file(int fd, t_data *data)
{
	int		ret;
	char	*line;
	int		hist_count;
	t_list	*hist_tail;

	hist_count = 0;
	line = NULL;
	hist_tail = NULL;
	ret = get_next_line(fd, &line);
	while (ret >= 0)
	{
		if (*line != '\0')
			get_history(&hist_count, &hist_tail, data, line);
		free(line);
		line = NULL;
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &line);
	}
}

void	save_history(t_data *data)
{
	int		fd;
	char	*tmp;

	fd = open(HIST_FILE, O_CREAT | O_TRUNC, 0666);
	close(fd);
	fd = open(HIST_FILE, O_APPEND | O_CREAT | O_RDWR, 0666);
	if (fd >= 0)
	{
		history_tail(data);
		while (data->history_index)
		{
			tmp = ft_strjoin(data->history_index->content, "\n");
			ft_putstr_fd(tmp, fd);
			free(tmp);
			data->history_index = data->history_index->previous;
		}
		close(fd);
	}
}
