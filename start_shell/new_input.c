/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:21:43 by keddib            #+#    #+#             */
/*   Updated: 2021/04/02 19:42:37 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		set_input_cmd(t_data *data, char **holder)
{
	char *tmp;

	tmp = data->input_cmd;
	data->input_cmd = ft_strjoin(*holder, data->input_cmd);
	free(*holder);
	free(tmp);
}

void		handl_signals_exit_status(t_data *data)
{
	if (g_exit_status > 0)
	{
		data->exit_status = g_exit_status;
		g_exit_status = 0;
	}
}

void		hundle_input(t_data *data, char **holder)
{
	handl_signals_exit_status(data);
	if (data->input_cmd[0] != '\0')
	{
		if (!(data->parse_tree = parser(data->input_cmd)))
		{
			ft_putstr_fd(PARSER_ERR, STDERR);
			data->exit_status = 258;
		}
		else
			execute(data);
	}
	*holder = ft_strdup("");
	free(data->input_cmd);
}

void		new_input(t_data *data, char **holder)
{
	int ret;

	data->no_status_check = 0;
	data->input_cmd = NULL;
	if (**holder == '\0' && !data->input_from_file)
	{
		ft_putstr_fd(PROMPT, STDOUT);
	}
	ret = get_next_line(0, &(data->input_cmd));
	set_input_cmd(data, holder);
	if (ret == 1 || (ret == 0 && (data->input_cmd[0] != '\0') &&
					data->input_from_file))
		hundle_input(data, holder);
	else if (ret == 0 && (data->input_cmd[0] == '\0'))
	{
		if (!data->input_from_file)
			ft_putstr_fd("exit\n", STDOUT);
		free_data(data);
		exit(0);
	}
	else if (!data->input_from_file)
		*holder = ft_strdup(data->input_cmd);
}
