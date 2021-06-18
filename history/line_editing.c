/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:53:31 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 12:07:00 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** QUIT and INT SIG while in listening for input
*/

int	set_sig(char **holder, t_data *data)
{
	int		brk;

	brk = 0;
	if (g_exit_status == -2)
		g_exit_status = 0;
	if (g_exit_status == -1)
	{
		data->exit_status = 1;
		g_exit_status = 0;
		free(*holder);
		*holder = ft_strdup("");
		brk = 1;
	}
	return (brk);
}

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

void	history_down(char **holder, t_data *data)
{
	char	*tmp;

	tmp = browse_history_down(&(data->history_index));
	free(*holder);
	*holder = ft_strdup("");
	if (tmp)
		*holder = ft_strdup(tmp);
	clear_line(data);
	if (tmp)
		ft_putstr_fd(*holder, STDERR);
}

void	delete_char(char **holder, t_data *data)
{
	if (*holder[0] != '\0')
		(*holder)[ft_strlen(*holder) - 1] = '\0';
	clear_line(data);
	ft_putstr_fd(*holder, STDERR);
}

void	end_of_file(t_data *data, char *holder)
{
	if (*holder == '\0')
	{
		tputs(data->termc->keyend, 1, putchar_2);
		free(holder);
		ft_putstr_fd("\nexit\n", STDERR);
		tcsetattr(STDIN, TCSANOW, &data->origin);
		save_history(data);
		free_data(data);
		exit(0);
	}
}

void	append_to_holder(char *buffer, char **holder, t_data *data)
{
	char	*tmp;

	tmp = *holder;
	*holder = ft_strjoin(*holder, buffer);
	free(tmp);
	clear_line(data);
	ft_putstr_fd(*holder, STDERR);
}

void	return_input(t_data *data, char *holder)
{
	write(STDERR, &"\n", 1);
	add_history(&(data->history_head), &(data->history_index), holder);
}
