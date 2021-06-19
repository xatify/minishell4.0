/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:18:25 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/19 08:22:12 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*holder;

	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	data = start_shell(argc, argv, envp, &holder);
	if (data->in_terminal)
		build_history(data);
	while (TRUE)
	{
		if (g_pid == -130 || g_pid == -131)
		{
			data->exit_status = -g_pid;
			g_pid = 0;
		}
		new_input(data, &holder);
		ft_lstclear(&(data->parse_tree), free_pipeline);
	}
	return (0);
}
