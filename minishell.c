/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:50:20 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/13 10:31:56 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int	argc, char **argv, char **envp)
{
	t_data 	*data;

	data = start_shell(argc, argv, envp);
	while (TRUE)
	{
		write(1, &PROMPT, ft_strlen(PROMPT));
		if (get_next_line(0, &(data->input_cmd)))
		{
			data->parse_tree = parser(data->input_cmd);
			show_pipeline(data->parse_tree);
		}
		free(data->input_cmd);
	}
	return (0);
}
