/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:21:43 by keddib            #+#    #+#             */
/*   Updated: 2021/04/04 19:27:25 by abbouzid         ###   ########.fr       */
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
	char	buffer[6];
	int		i;
	char	*tmp;

	while (TRUE)
	{
		ft_memset(buffer, 0, 6);
		tcsetattr(STDIN, TCSANOW, &data->modified);
		i = read(STDIN, &buffer, 5);
		/* QUIT SIG keep listening for input */
		if (g_exit_status == -2)
		{
			g_exit_status = 0;
			continue;
		}
		/* INT SIG throw the data */
		if (g_exit_status == -1)
		{
			free(*holder);
			*holder = ft_strdup("");
			break;
		}
		ft_putstr_fd(buffer, 2);
		/* browse history up */
		if (!ft_strcmp(data->termc->up_key, buffer))
		{
			if (data->history_index == NULL)
				data->history_index =  data->history_head;
			if (data->history_head && data->history_head->next == NULL)
			{
				free(*holder);
				*holder = ft_strdup(data->history_head->content);
				clear_line(data);
				ft_putstr_fd(*holder, STDERR);
			}
			else if ((tmp = browse_history_up(&(data->history_index))))
			{
				free(*holder);
				*holder = ft_strdup(tmp);
				clear_line(data);
				ft_putstr_fd(*holder, STDERR);
				/*clear the line && print (*holder) */
			}
		}
		/* browse history down */
		else if (!ft_strcmp(data->termc->down_key, buffer))
		{
			if ((tmp = browse_history_down(&(data->history_index))))
			{
				free(*holder);
				*holder = ft_strdup(tmp);
				clear_line(data);
				ft_putstr_fd(*holder, STDERR);
				/*clear the line && print (*holder) */
			}
			else
			{
				free(*holder);
				*holder = ft_strdup("");
				clear_line(data);
			}
		}
		/* EOF received */
		else if (ft_strlen(buffer) == 1 && buffer[0] == '\x04')
		{
			tcsetattr(STDIN, TCSANOW, &data->origin);
			write(STDERR, &"\n", 1);
			exit(0);
		}
		/* buffer == new line*/
		else if (ft_strlen(buffer) == 1 && buffer [0] == '\n')
		{
			write(STDOUT, buffer, 1);
			data->input_cmd = ft_strdup(*holder);
			add_history(&(data->history_head), &(data->history_index),  *holder);
			free(*holder);
			*holder = ft_strdup("");
			break;
		}
		/* delete key */
		else if (!ft_strcmp(data->termc->erase, buffer))
		{
			if (*holder[0] != '\0')
				(*holder)[ft_strlen(*holder) - 1] = '\0';
			clear_line(data);
			ft_putstr_fd(*holder, STDERR);
			continue;
		}
		/* append buffer to holder if buffer is not new line or buffer is EOF */
		else if (((buffer[0] >= 32  && buffer[0] <= 126) || buffer[0] == 9) && i == 1)
		{
			tmp = *holder;
			*holder = ft_strjoin(*holder, buffer);
			free(tmp);
			clear_line(data);
			ft_putstr_fd(*holder, STDERR);
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
