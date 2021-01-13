/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:49:46 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/13 14:52:56 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "structs.h"
#include "tokens.h"
#include "lexer.h"
#include "stack.h"
#include "strmanip.h"
#include "env_var.h"
#include "parser.h"
#include "builtins.h"
#include "strlist.h"
#include "simple_command.h"
#include "pipeline.h"
#include "expansion.h"
#include "get_input.h"
#include "init_shell.h"
#include "execution.h"

/*
** building argv array from linked list
*/

char    **build_argv(t_simple_command *cmd);
void    free_argv(char **argv);

/*
** search for binary file and programs
*/

char    *find_binary_file(char *cmd_name);
char    *get_bins_path(t_data *data);
char    *absolute_path(char *cmd, char *PATH);

#endif
