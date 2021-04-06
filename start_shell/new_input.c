/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:21:43 by keddib            #+#    #+#             */
/*   Updated: 2021/04/06 15:29:47 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void		handl_signals_exit_status(t_data *data)
{
	if (g_exit_status < 0)
	{
		data->exit_status = 1;
		g_exit_status = 0;
	}
}

void		hundle_input(t_data *data, char **holder)
{
	data->input_cmd = ft_strdup(*holder);
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
	free(data->input_cmd);
	*holder = ft_strdup("");
}

void	non_canonical_mode(t_data *data, char **holder)
{
	char	buffer[4];
	int		i;

	tputs(data->termc->keystart, 1, putchar_2);
	while (TRUE)
	{
		ft_memset(buffer, 0, 4);
		tcsetattr(STDIN, TCSANOW, &data->modified);
		i = read(STDIN, &buffer, 3);
		if (set_sig(holder, data))
			break;
		if (!ft_strcmp(buffer, data->termc->up_key))
			history_up(holder, data);
		else if (!ft_strcmp(data->termc->down_key, buffer))
			history_down(holder, data);
		else if (buffer[0] == '\x04')
			end_of_file(data, *holder);
		else if (buffer[0] == 127)
		{
			delete_char(holder, data);
			continue;
		}
		else if (is_print(buffer[0]) && buffer[1] == '\0')
			append_to_holder(buffer, holder, data);
		else if (buffer[0] == '\n' || buffer[0] == '\r')
		{
			return_input(data, *holder);
			break;
		}
	}
}

void		new_input(t_data *data, char **holder)
{
	int ret;

	data->no_status_check = 0;
	data->input_cmd = NULL;
	if (data->in_terminal)
	{
		ft_putstr_fd(PROMPT, STDERR);
		non_canonical_mode(data, holder);
		tcsetattr(STDIN, TCSANOW, &data->origin);
		hundle_input(data, holder);
		//ft_putchar_fd('\n', STDERR);
	}
	else
	{
		ret = get_next_line(STDIN, &data->input_cmd);
		if (ret == 1 || (ret == 0 && (data->input_cmd[0] != '\0')))
			hundle_input(data, holder);
	}
}
