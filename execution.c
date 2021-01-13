/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/13 12:19:54 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char    *get_bins_path(t_data *data)
{
    t_env_vars      *bins_path;
    
    bins_path = search_var(data->env_vars, "PATH");
    if (!bins_path)
        return (NULL);
    return (bins_path->name);
}


char    *absolute_path(char *cmd_name, char *PATH_ENV)
{
}

int     execute_built_in(char built_in, t_data *data, t_simple_command *cmd)
{
    char    **argv;

    argv = build_argv(cmd);
    if (built_in == 'c')
        return (cd(argv[1], data->env_vars));
    else if (built_in == 'e')
        return (echo(argv));
    else if (built_in == 'n')
        return (env(data->env_vars));
    else if (built_in == 'u')
        return (unset(argv, data->env_vars));
    else if (built_in == 'p')
        return (export(argv, data->env_vars));
    else if (built_in == 'w')
        return (pwd());
    exit_(data, 0);
}

int     execute_binary(t_data *data, t_simple_command *cmd)
{
    char        *path;
    char        *bins_dirs;
    pid_t       pid;

        
    bins_dirs = get_bins_path(data);
    if (!bins_dirs)
    {
        printf("command not found\n");
        return (0);
    }
    path = absolute_path(cmd->cmd_name, bins_dirs);
    if (!path)
    {
        printf("no such file or directory\n");
        return (0);
    }
    pid = fork();
    
}

void    execute_simple_cmd(t_data *data, t_simple_command *cmd)
{
    char    built_in;

    built_in = is_build_in(cmd->cmd_name);
    if (built_in != '\0')
        *(data->exit_status) = execute_built_in(built_in, data, cmd);
    else
        *(data->exit_status) = execute_binary(data, cmd);
}

int     execute(t_data   *data)
{
        
}

