/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:21:43 by keddib            #+#    #+#             */
/*   Updated: 2021/06/27 15:46:08 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_exit_status(t_data *data)
{
	if (g_pid == -1)
	{
		data->exit_status = 1;
		g_pid = 0;
	}
	if (!data->input_cmd)
	{
		free_data(data);
		exit(0);
	}
}

void	new_input(t_data *data)
{
	int	error;

	error = 0;
	data->input_cmd = NULL;
	data->input_cmd = readline(PROMPT);
	set_exit_status(data);
	if (data->input_cmd[0])
	{
		data->parse_tree = parser(data->input_cmd, &error);
		if (!data->parse_tree || error)
		{
			ft_putstr_fd(PARSER_ERR, STDERR);
			data->exit_status = 258;
		}
		else
			execute(data);
		add_history(data->input_cmd);
	}
	free(data->input_cmd);
}
