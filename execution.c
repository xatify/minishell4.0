/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/28 10:24:26 by abbouzid         ###   ########.fr       */
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
    return (ret);
}

int    execute_child(t_data *data, t_simple_command *cmd)
{
    char        *path;
    char        **argv;
    char        **envp;

    path = find_binary_file(data, cmd->cmd_name);
    argv = built_argv(cmd);
    envp = built_envp(data->env_vars);
    ////// problem
    if (!path)
    {
        ft_putstr_fd("no such file or directory\n", 2);
        exit(127);
    }
    signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    execve(path, argv, envp);
    ft_putstr_fd("no such file or directory 2\n", 2);
    exit(126);
}

int     execute_binary(t_data *data, t_simple_command *cmd)
{
    int         status;

    g_pid = fork();
    if (g_pid == 0)
    {
        exit(execute_child(data, cmd));
    }
    else if (g_pid < 0)
        return (1);
    waitpid(g_pid, &status, 0); // must check status
    g_pid = -1;
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (status);
}

int    execute_simple_cmd(t_data *data, t_simple_command *cmd)
{
    int save_std[2];
    int tmp_fd[2];

    save_std[0] = dup(STDIN);
    save_std[1] = dup(STDOUT);
    if (cmd)
    {
        if (!simple_cmd_file_redirection(cmd, save_std, tmp_fd))
            return (0);
        if (cmd->cmd_name)
        {
            if (cmd->built_in != '\0')
                data->exit_status = execute_built_in(cmd->built_in, data, cmd);
            else
                data->exit_status = execute_binary(data, cmd);
        }
        set_to_std(save_std);
    }
    return (1);
}

void    execute_pipeline(t_data *data, t_pipeline *pipeline)
{
    int                 tmp_fd[2];
    int                 save_std[2];
    int                 status;
    t_simple_command    *cmd;


    save_std[0] = dup(STDIN);
    save_std[1] = dup(STDOUT);

    cmd = pipeline->simple_cmd;
    tmp_fd[0] = dup(save_std[0]);
    tmp_fd[1] = dup(save_std[1]);
    while (cmd)
    {
        if (!pipeline_stream(cmd, save_std, tmp_fd))
        {
            tmp_fd[0] = dup(save_std[0]);
            tmp_fd[1] = dup(save_std[1]);
            cmd = cmd->next;
            continue;
        }
        if (cmd->cmd_name)
        {
            if (cmd->built_in != '\0' && ft_strcmp(cmd->cmd_name, "cd") != 0)
                data->exit_status = execute_built_in(cmd->built_in, data, cmd);
            else
            {
                g_pid = fork();
                if (g_pid == 0)
                    execute_child(data, cmd);
                else if (g_pid < 0)
                    data->exit_status = 1;
            }
        }
        cmd = cmd->next;
    }
    set_to_std(save_std);
    waitpid(g_pid, &status, 0);
    g_pid = -1;
    if (WIFEXITED(status))
        data->exit_status = WEXITSTATUS(status);
    else
        data->exit_status = status;
}

void    execute(t_data *data, t_pipeline *pipeline)
{
    while (pipeline)
    {
        if (expand_pipeline(pipeline, data))
        {
            if (pipeline->simple_cmd->next)
                execute_pipeline(data, pipeline);
            else
                execute_simple_cmd(data, pipeline->simple_cmd);
        }
        else
            data->exit_status = 1;
        pipeline = pipeline->next;
    }
}
