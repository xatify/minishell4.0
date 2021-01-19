/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/19 12:51:46 by abbouzid         ###   ########.fr       */
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
    char        **envp;

    path = find_binary_file(data, cmd->cmd_name);
    if (!path)
    {
        ft_putstr_fd("no such file or directory\n", 2);
        return (1);
    }
    argv = built_argv(cmd);
    envp = built_envp(data->env_vars);
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
        return (status);
    }
}

int    execute_simple_cmd(t_data *data, t_simple_command *cmd)
{
    int     pipe_fd[2];
    int     outfile;
    int     infile;

    outfile = -1;
    infile = -1;
    if (cmd)
    {
        if (!redirect_stdin(cmd, &infile))
            return (0);
        if (infile != -1)
        {
            dup2(data->tmp_in, infile);
            close(infile);
        }
        if (!redirect_stdout(cmd, &outfile))
            return (0);
        if (outfile != -1)
        {
            dup2(data->tmp_out, outfile);
            close(outfile);
        }
        else
        {
            if (cmd->next)
            {
                if (pipe(pipe_fd) < 0)
                    return (0);
                data->tmp_out = pipe_fd[STDOUT];
                data->tmp_in = pipe_fd[STDIN];
                close(pipe_fd[STDIN]);
            }
        }
        if (cmd->built_in != '\0')
            data->exit_status = execute_built_in(cmd->built_in, data, cmd);
        else
            data->exit_status = execute_binary(data, cmd);
        return (execute_simple_cmd(data, cmd->next));
    }
    return (1);
}

void    execute_pipeline(t_data *data, t_pipeline *pipeline)
{
    int tmp_in;
    int tmp_out;

    tmp_in = dup(0);
    tmp_out = dup(1);
    if (pipeline)
    {
        if (expand_pipeline(pipeline, data))
        {
            if (!execute_simple_cmd(data, pipeline->simple_cmd))
                data->exit_status = 1;
            dup2(tmp_in, 0);
            dup2(tmp_out, 1);
        }
        execute_pipeline(data, pipeline->next);
    }
}

void     execute(t_data   *data)
{
    execute_pipeline(data, data->parse_tree);
}
