/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:21:32 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/09 08:14:44 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_int_handler(int signum)
{
	if (g_pid > 0)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n", 1);
		kill(g_pid, SIGINT);
	}
	else
	{
		g_exit_status = 1;
		ft_putstr_fd("\b\b  \b\b\n", 1);
		ft_putstr_fd(PROMPT, 1);
	}
	(void)signum;
}

void	sig_quit_handler(int signum)
{
	if (g_pid > 0)
	{
		g_exit_status = 131;
		ft_putstr_fd("QUIT: 3\n", 1);
		kill(g_pid, SIGQUIT);
	}
	else
	{
		g_exit_status = 1;
		ft_putstr_fd("\b\b  \b\b", 1);
	}
	(void)signum;
}
