/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:18:25 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/26 09:58:28 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int	argc, char **argv, char **envp)
{
	t_data 	*data;

	data = start_shell(argc, argv, envp);
	
	while (TRUE)
	{
		signal(SIGINT, sig_int_handler);
		signal(SIGQUIT, sig_quit_handler);
		ft_putstr_fd(PROMPT, 1);
		if (get_next_line(0, &(data->input_cmd)))
		{
			//printf("%s\n", data->input_cmd);
			data->parse_tree = parser(data->input_cmd);
			execute(data, data->parse_tree);
		}
	}
	return (0);
}