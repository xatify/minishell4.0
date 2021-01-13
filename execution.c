/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/13 15:07:15 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"





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
    pid_t       child_pid;
    int         status;
    char        **argv;

    path = find_binary_file(cmd->cmd_name);
    if (!path)
    {
        printf("no such file or directory\n");
        return (1);
    }
    child_pid = fork();
    argv = build_argv(cmd);
    if (child_pid == 0)
    {
        execve(path, argv, NULL);
        printf("execve error\n");
        return (1);
    }
    else if (child_pid < 0)
        return (1);
    else
    {
        waitpid(child_pid, &status, 0); // must check status
        free(path);
        free_argv(argv);
        return (status);
    }
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
