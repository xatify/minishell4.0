/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:21:32 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/22 10:54:11 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    sig_int_handler(int signum)
{
    
    printf("\n%d:hello world\n", signum);
}

// void    sig_quit_handler(int signum)
// {  
// }