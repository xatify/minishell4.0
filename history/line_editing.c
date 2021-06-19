/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:53:31 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/19 12:53:06 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** QUIT and INT SIG while in listening for input
*/

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
