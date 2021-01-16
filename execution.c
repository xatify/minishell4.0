/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/16 10:50:47 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int     execute_built_in(char built_in, t_data *data, t_simple_command *cmd)
{
    int     ret;
    char    **argv;

    argv = built_argv(cmd);
    ret = 0;
    if (built_in == 'c')
        ret = cd(argv[1], &(data->env_vars));
    else if (built_in == 'e')
        ret = echo(argv);
    else if (built_in == 'n')
        ret = env(argv[1], data->env_vars);
    else if (built_in == 'u')
        ret = unset(argv, &(data->env_vars));
    else if (built_in == 'p')
        ret = export(argv, data);
    else if (built_in == 'w')
        ret = pwd();
    else
        exit_(data, argv);
    //free_argv(argv);
    return (ret);
}

int     execute_binary(t_data *data, t_simple_command *cmd)
{
    char        *path;
    pid_t       child_pid;
    int         status;
    char        **argv;
    char        *envp[1] = {0};

    path = find_binary_file(data, cmd->cmd_name);
    if (!path)
    {
        ft_putstr_fd("no such file or directory\n", 2);
        return (1);
    }
    argv = built_argv(cmd);
    child_pid = fork();
    if (child_pid == 0)
    {
        execve(path, argv, envp);
        return (1);
    }
    else if (child_pid < 0)
        return (1);
    else
    {
        waitpid(child_pid, &status, 0); // must check status
        free(path);
        //free_argv(argv);
        return (status);
    }
}

void    execute_simple_cmd(t_data *data, t_simple_command *cmd)
{
    char    built_in;

    if (cmd)
    {
        if (expand_cmd(cmd, data->env_vars, &(data->exit_status)))
        {
            built_in = is_built_in(cmd->cmd_name);
            if (built_in != '\0')
                data->exit_status = execute_built_in(built_in, data, cmd);
            else
                data->exit_status = execute_binary(data, cmd);
        }
        execute_simple_cmd(data, cmd->next);
    }
}

void    execute_pipeline(t_data *data, t_pipeline *pipeline)
{
    if (pipeline)
    {
        execute_simple_cmd(data, pipeline->simple_cmd);
        execute_pipeline(data, pipeline->next);
    }
}

void     execute(t_data   *data)
{
    execute_pipeline(data, data->parse_tree);
}
