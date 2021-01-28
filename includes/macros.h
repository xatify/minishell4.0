/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:16:16 by keddib            #+#    #+#             */
/*   Updated: 2021/01/28 09:16:00 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** macros
*/

#define SHELL "/bin/sh"
#define PROMPT "minishell-2.0$ "

#define TRUE 1
#define FALSE 0
#define STDIN 0
#define STDOUT 1
#define bool int

int     g_pid;
int     g_exit_status;
#endif
