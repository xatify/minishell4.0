/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:21:32 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/19 08:42:10 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_int_handler(int signum)
{
	if (g_pid > 0)
	{
		ft_putstr_fd("\n", STDERR);
		g_pid = -130;
		kill(g_pid, SIGINT);
	}
	else
	{
		ft_putchar_fd('\n', STDERR);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_pid = -1;
	}
	(void)signum;
}

void	sig_quit_handler(int signum)
{
	//printf("%d\n", g_pid);
	if (g_pid > 0)
	{
		g_pid = -131;
		ft_putstr_fd("QUIT: 3\n", STDERR);
		kill(g_pid, SIGQUIT);
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
	(void)signum;
}
