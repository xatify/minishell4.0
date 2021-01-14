/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/13 17:46:12 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int     execute_built_in(char built_in, t_data *data, t_simple_command *cmd)
{
    char    **argv;

    argv = built_argv(cmd);
    if (built_in == 'c')
        return (cd(argv[1], &(data->env_vars)));
    else if (built_in == 'e')
        return (echo(argv));
    else if (built_in == 'n')
        return (env(data->env_vars));
    else if (built_in == 'u')
        return (unset(argv, &(data->env_vars)));
    else if (built_in == 'p')
        return (export(argv, &(data->env_vars)));
    else if (built_in == 'w')
        return (pwd());
    exit_(data, 0);
    return (0);
}

int     execute_binary(t_data *data, t_simple_command *cmd)
{
    char        *path;
    pid_t       child_pid;
    int         status;
    char        **argv;
    //char        **envp;

    path = find_binary_file(data, cmd->cmd_name);
    if (!path)
    {
        printf("no such file or directory\n");
        return (1);
    }
    child_pid = fork();
    argv = built_argv(cmd);
    if (child_pid == 0)
    {
        printf("path : %s\n", path);
        int i = 0;
        ft_printf("args :");
        while (argv[i])
        {
            ft_printf(" %s", argv[i]);
            i++;
        }
        execv(path, argv);
        printf("execve error\n");
        return (1);
    }
    else if (child_pid < 0)
        return (1);
    else
    {
        waitpid(child_pid, &status, 0); // must check status
        //free(path);
        //free_argv(argv);
        return (status);
    }
}

void    execute_simple_cmd(t_data *data, t_simple_command *cmd)
{
    char    built_in;

    if (cmd)
    {
        built_in = is_built_in(cmd->cmd_name);
        if (built_in != '\0')
            *(data->exit_status) = execute_built_in(built_in, data, cmd);
        else
            execute_binary(data, cmd);
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
