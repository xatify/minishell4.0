/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:16:16 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 19:01:33 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** macros
*/

# define PROMPT "minishell-4.0$ "

# define TRUE			1
# define FALSE			0
# define STDIN			0
# define STDOUT			1
# define STDERR 		2
# define OUTPUT			0
# define INPUT			1
# define APPEND_OUT		2
# define PIPE			3
# define SEMICOLON		4
# define WORD			5
# define BOOL			int
# define RM_PATH		"cd: error retrieving current directory\n"
# define NO_F_D			"no such file or directory\n"
# define ARG_NOT_SUP	"env arg not supported yet\n"
# define MANY_ARGS		"exit: too many arguments\n"
# define NUM_ARG_R		"exit: numeric argument required\n"
# define NOT_IDEN		"not a valid identifier "
# define P_DENIED		"minishell: Permission denied\n"
# define EXPAN_ERR		"error while expanding !\n"
# define PARSER_ERR		"error while parsing !\n"
# define AMB_REDIRECT	": ambiguous redirect\n"
# define HIST_FILE		"./.minishell_history"
# define HIST_SIZE		20

typedef struct termios	t_termios;
int						g_pid;
int						g_exit_status;

#endif
