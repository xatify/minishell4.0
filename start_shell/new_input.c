/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:21:43 by keddib            #+#    #+#             */
/*   Updated: 2021/04/03 19:08:24 by abbouzid         ###   ########.fr       */
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
	//free(data->input_cmd);
}

void	non_canonical_mode(t_data *data, char **holder)
{
	char	buffer[4];
	int		i;
	char	*tmp;

	while (TRUE)
	{
		ft_memset(buffer, 0, 4);
		tcsetattr(STDIN, TCSANOW, &data->modified);
		i = read(STDIN, &buffer, 3);
		if (g_exit_status == -1)
		{
			ft_putstr_fd("\n", STDERR);
			free(*holder);
			*holder = ft_strdup("");
			break;
		}
		if (i == -1)
		{
			free_data(data);
			free(*holder);
			exit(1);
		}
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
		{
			ft_putstr_fd("UP ARROW KEY pressed\n", STDOUT);
			exit(1);
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
		{
			ft_putstr_fd("DOWN ARROW KEY pressed\n", STDOUT);
			exit(1);
		}
		else if (buffer[0] != '\n' && buffer[0] != '\x04')
		{
			tmp = *holder;
			*holder = ft_strjoin(*holder, buffer);
			free(tmp);
			write(STDOUT, buffer, 1);
		}
		else if (buffer[0] == '\x04')
		{
			tcsetattr(STDIN, TCSANOW, &data->origin);
			write(STDERR, &"\n", 1);
			exit(0);
		}
		else
		{
			write(STDOUT, buffer, 1);
			data->input_cmd = ft_strdup(*holder);
			free(*holder);
			*holder = ft_strdup("");
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
		if (g_exit_status < 0)
		{
			data->exit_status = 1;
			g_exit_status = 0;
		}
		else
			hundle_input(data, holder);
	}
	else
	{
		ret = get_next_line(STDIN, &data->input_cmd);
		if (ret == 1 || (ret == 0 && (data->input_cmd[0] != '\0')))
			hundle_input(data, holder);
		else if (ret == 0 && (data->input_cmd[0] == '\0'))
		{
			if (data->in_terminal)
				ft_putstr_fd("exit\n", STDOUT);
			free_data(data);
			exit(0);
		}
		else if (data->in_terminal)
			*holder = ft_strdup(data->input_cmd);
	}
}
