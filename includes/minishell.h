/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:49:46 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/19 12:03:02 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

# include "macros.h"
# include "structs.h"
# include "tokens.h"
# include "lexer.h"
# include "stack.h"
# include "str_manip.h"
# include "env_var.h"
# include "parser.h"
# include "builtins.h"
# include "simple_command.h"
# include "pipeline.h"
# include "expansion.h"
# include "get_input.h"
# include "init_shell.h"
# include "execution.h"
# include "find_binary.h"
# include "variables.h"
# include "sort.h"
# include "redirection.h"
# include "arguments_array.h"
# include "sig_handling.h"
# include "history.h"
# include "lst_methods.h"

#endif
