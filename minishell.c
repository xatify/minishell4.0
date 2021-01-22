/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:18:25 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/22 10:53:55 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int	argc, char **argv, char **envp)
{
	t_data 	*data;

	data = start_shell(argc, argv, envp);
	//signal(SIGINT, sig_int_handler);
	while (TRUE)
	{
		show_prompt(data);
		if (get_next_line(0, &(data->input_cmd)))
		{
			data->parse_tree = parser(data->input_cmd);
			execute(data, data->parse_tree);
		}
	}
	return (0);
}