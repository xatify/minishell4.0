/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:21:43 by keddib            #+#    #+#             */
/*   Updated: 2021/06/23 17:19:44 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_input(t_data *data)
{
	int	ret;
	
	data->input_cmd = NULL;
	ft_putstr_fd(PROMPT, 2);
	ret = get_next_line(0, &(data->input_cmd));
	if (ret >= 0 && (data->input_cmd[0]))
	{
		data->parse_tree = parser(data->input_cmd);
		if (!data->parse_tree)
		{
			ft_putstr_fd(PARSER_ERR, STDERR);
			data->exit_status = 258;
		}
		else
			execute(data);
	}
	free(data->input_cmd);
}
