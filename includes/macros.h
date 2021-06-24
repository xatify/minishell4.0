/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:16:16 by keddib            #+#    #+#             */
/*   Updated: 2021/06/23 17:17:56 by abbouzid         ###   ########.fr       */
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
# define HEREDOC		3
# define PIPE			4
# define SEMICOLON		5
# define WORD			6
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

volatile sig_atomic_t	g_pid;

#endif
