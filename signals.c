/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:21:32 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/26 09:59:17 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    sig_int_handler(int signum)
{
    if (g_pid > 0)
    {
        ft_putstr_fd("\n", 0);
        kill(g_pid, SIGINT);
    }
    else
    {
        
        ft_putstr_fd("\n\b", 1);
        ft_putstr_fd(PROMPT, 1);
    //ft_putstr_fd("\n", 0);
    }
    (void)signum;
    return;
}

void    sig_quit_handler(int signum)
{
    if (g_pid > 0)
    {
        ft_putstr_fd("QUIT: 3\n", 1);
        kill(g_pid, SIGQUIT);
    }
    else
    {
        ft_putstr_fd("\b\b\r", 0);
        ft_putstr_fd(PROMPT, 1);
    }
    (void)signum;
    return;
}
