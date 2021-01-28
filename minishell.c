/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:18:25 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/28 09:16:48 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int	argc, char **argv, char **envp)
{
	t_data 	*data;

	g_exit_status = 0;
	data = start_shell(argc, argv, envp);
	
	while (TRUE)
	{
		signal(SIGINT, sig_int_handler);
		signal(SIGQUIT, sig_quit_handler);
		ft_putstr_fd(PROMPT, 1);
		if (get_next_line(0, &(data->input_cmd)))
		{
			if (g_exit_status > 0)
			{
				data->exit_status = g_exit_status;
				g_exit_status = 0;
			}
			//printf("%s\n", data->input_cmd);
			data->parse_tree = parser(data->input_cmd);
			execute(data, data->parse_tree);
		}
	}
	return (0);
}