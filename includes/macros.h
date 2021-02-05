/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:16:16 by keddib            #+#    #+#             */
/*   Updated: 2021/02/03 11:15:13 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** macros
*/

# define PROMPT "minishell-3.0$ "

# define TRUE 1
# define FALSE 0
# define STDIN 0
# define STDOUT 1
# define BOOL int
# define OUTPUT 0
# define INPUT 1
# define APPEND_OUT 2
# define PIPE 3
# define SEMICOLON 4
# define WORD 5

int			g_pid;
int			g_exit_status;

#endif
