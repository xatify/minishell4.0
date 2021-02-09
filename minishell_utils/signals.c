/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:21:32 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/09 15:41:54 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_int_handler(int signum)
{
	if (g_pid > 0)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n", STDOUT);
		kill(g_pid, SIGINT);
	}
	else
	{
		g_exit_status = 1;
		ft_putstr_fd("\b\b  \b\b\n", STDOUT);
		ft_putstr_fd(PROMPT, STDOUT);
	}
	(void)signum;
}

void	sig_quit_handler(int signum)
{
	if (g_pid > 0)
	{
		g_exit_status = 131;
		ft_putstr_fd("QUIT: 3\n", STDOUT);
		kill(g_pid, SIGQUIT);
	}
	else
	{
		g_exit_status = 1;
		ft_putstr_fd("\b\b  \b\b", STDOUT);
	}
	(void)signum;
}
