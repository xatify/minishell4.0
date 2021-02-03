/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/03 10:52:30 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int     execute_built_in(char built_in, t_data *data, t_command *cmd)
{
    int     ret;
    char    **argv;

    argv = built_argv(cmd);
    ret = 0;
    if (built_in == 'c')
        ret = cd(argv[1], data);
    else if (built_in == 'e')
        ret = echo(argv);
    else if (built_in == 'n')
        ret = env(argv[1], data->env_vars);
    else if (built_in == 'u')
        ret = unset(argv, &(data->env_vars));
    else if (built_in == 'p')
        ret = export(argv, data);
    else if (built_in == 'w')
        ret = pwd(data);
    else
        ret = exit_(data, argv);
    return (ret);
}


int    execute_child(t_data *data, t_command *cmd)
{
    char        *path;
    char        **argv;
    char        **envp;

    path = find_binary_file(data, cmd->name_and_args->content);
    argv = built_argv(cmd);
    envp = built_envp(data->env_vars);
    if (!path)
    {
        ft_putstr_fd("no such file or directory : ", 2);
        ft_putstr_fd(cmd->name_and_args->content, 2);
        ft_putstr_fd("\n", 1);
        exit(127);
    }
    signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    execve(path, argv, envp);
    ft_putstr_fd("no such file or directory 2\n", 2);
    exit(126);
}

int     execute_binary(t_data *data, t_command *cmd)
{
    int         status;

    g_pid = fork();
    if (g_pid == 0)
    {
        execute_child(data, cmd);
    }
    else if (g_pid < 0)
        return (1);
    waitpid(g_pid, &status, 0); // must check status
    g_pid = -1;
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (status);
}

void    execute_simple_cmd(t_data *data, t_pipeline *pipeline)
{
    t_command       *cmd;
    int             save_std[2];
    int             tmp_fd[2];
    char            *name_and_args;

    save_std[0] = dup(STDIN);
    save_std[1] = dup(STDOUT);
    if ((cmd = (t_command *)(pipeline->cmds->content)))
    {
        if (!simple_cmd_file_redirection(cmd, save_std, tmp_fd))
            return;
        name_and_args = cmd->name_and_args->content;
        if (name_and_args[0])
        {
            cmd->built_in = is_built_in(name_and_args);
            if (cmd->built_in != '\0')
                data->exit_status = execute_built_in(cmd->built_in, data, cmd);
            else
                data->exit_status = execute_binary(data, cmd);
        }
    }
    set_to_std(save_std);
}

void    set_fds(int save_std[2], int tmp_fd[2])
{
    save_std[0] = dup(STDIN);
    save_std[1] = dup(STDOUT);
    copy_fds(tmp_fd, save_std);
}

void     return_status(int status, t_data *data)
{
    if (WIFEXITED(status))
        data->exit_status = WEXITSTATUS(status);
    else
        data->exit_status = status;
}

void    execute_pipe(t_command *cmd, t_data *data)
{
    char                *name_and_args;
    
    name_and_args = cmd->name_and_args->content;
    if (name_and_args[0])
    {
        cmd->built_in = is_built_in(name_and_args);
        if (cmd->built_in != '\0' && ft_strcmp(name_and_args, "cd") != 0)
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
}


void    execute_pipeline(t_data *data, t_list *cmds)
{
    int                 tmp_fd[2];
    int                 save_std[2];
    int                 status;
    t_command           *cmd;

    set_fds(save_std, tmp_fd);
    while (cmds)
    {
        cmd = (t_command *)(cmds->content);
        if (!pipeline_stream(cmd, save_std, tmp_fd, cmds))
            continue;
        execute_pipe(cmd, data);
        cmds = cmds->next;
    }
    set_to_std(save_std);
    waitpid(g_pid, &status, 0);
    g_pid = -1;
    return_status(status, data);
}

void    execute(t_data *data)
{
    t_list      *pipelines;
    t_pipeline *pipeline;
    
    pipelines = data->parse_tree;
    while (pipelines)
    {
        pipeline = (t_pipeline *)(pipelines->content);
        if (expand_pipeline(pipeline, data))
        {
            if (pipeline->cmds->next)
                execute_pipeline(data, pipeline->cmds);
            else
                execute_simple_cmd(data, pipeline);
        }
        pipelines = pipelines->next;
    }
}
