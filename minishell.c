/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:18:25 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/30 12:18:17 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	argc = 0;
	argv = NULL;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	start_shell(&data, envp);
	while (TRUE)
	{
		if (g_pid == -130 || g_pid == -131)
			data.exit_status = -g_pid;
		if (g_pid == -1)
			data.exit_status = 1;
		g_pid = 0;
		new_input(&data);
		ft_lstclear(&(data.parse_tree), free_pipeline);
	}
	return (0);
}
