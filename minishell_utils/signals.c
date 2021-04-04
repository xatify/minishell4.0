/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:21:32 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/04 12:03:13 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_int_handler(int signum)
{
	ft_putstr_fd("\n", STDERR);
	if (g_pid > 0)
	{
		g_exit_status = 130;
		kill(g_pid, SIGINT);
	}
	else
		g_exit_status = -1;
	(void)signum;
}

void	sig_quit_handler(int signum)
{
	if (g_pid > 0)
	{
		g_exit_status = 131;
		ft_putstr_fd("QUIT: 3\n", STDERR);
		kill(g_pid, SIGQUIT);
	}
	else
	{
		g_exit_status = -2;
	}
	(void)signum;
}



