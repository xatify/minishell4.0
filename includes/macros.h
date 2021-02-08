/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:16:16 by keddib            #+#    #+#             */
/*   Updated: 2021/02/08 17:15:46 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** macros
*/

# define PROMPT "minishell-4.0$ "

# define TRUE		1
# define FALSE		0
# define STDIN		0
# define STDOUT		1
# define STDERR 	2
# define OUTPUT		0
# define INPUT		1
# define APPEND_OUT 2
# define PIPE		3
# define SEMICOLON	4
# define WORD		5
# define BOOL		int

int			g_pid;
int			g_exit_status;
int			g_reading;

#endif
