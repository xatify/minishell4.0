/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/22 08:20:47 by abbouzid         ###   ########.fr       */
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

int     execute_binary(t_data *data, t_simple_command *cmd)
{
    char        *path;
    pid_t       pid;
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
    pid = fork();
    if (pid == 0)
    {
        execve(path, argv, envp);
        return (1);
    }
    else if (pid < 0)
        return (1);
    else
    {
        waitpid(pid, &status, 0); // must check status
        free(path);
        return (status);
    }
}

int    execute_simple_cmd(t_data *data, t_simple_command *cmd)
{
    int tmp_out;
    int tmp_in;
    int fdout;
    int fdin;
    
    tmp_in = dup(STDIN);
    tmp_out = dup(STDOUT);
    if (cmd)
    {
        fdout = tmp_out;
        fdin = tmp_in;
        if (!redirect_stdin(cmd, &fdin) || !redirect_stdout(cmd, &fdout))
        {
            close(tmp_in);
            close(tmp_out);
            return (0);  
        }
        dup2(fdout, STDOUT);
        dup2(fdin, STDIN);
        if (cmd->built_in != '\0')
            data->exit_status = execute_built_in(cmd->built_in, data, cmd);
        else
            data->exit_status = execute_binary(data, cmd);
        dup2(tmp_in, STDIN);
        dup2(tmp_out, STDOUT);
        close(tmp_in);
        close(tmp_out);
    }
    return (1);
}

void    execute_pipeline(t_data *data, t_pipeline *pipeline)
{
    int     tmp_in;
    int     tmp_out;
    int     fdin;
    int     fdout;
    int     ret;
    int     tmp;
    char        **argv;
    char        **envp;
    t_simple_command *cmd;
    int             pipefd[2];
    

    tmp_in = dup(STDIN);
    tmp_out = dup(STDOUT);
    
    cmd = pipeline->simple_cmd;
    fdin = dup(tmp_in);
    fdout = dup(tmp_out);
    while (cmd)
    {
        if (!redirect_stdin(cmd, &fdin))
            break;
        dup2(fdin, STDIN);
        close(fdin);
        tmp = -1;
        if (!redirect_stdout(cmd, &tmp))
            break;
        else
        {
            if (tmp != -1)
                fdout = tmp;
            else
            {
                if (!cmd->next)
                    fdout = dup(tmp_out);
                else
                {
                    pipe(pipefd);
                    fdout = pipefd[1];
                    fdin = pipefd[0];
                }
            }
        }
        dup2(fdout, STDOUT);
        close(fdout);
        if (cmd->built_in != '\0' && ft_strcmp(cmd->cmd_name, "cd") != 0)
            data->exit_status = execute_built_in(cmd->built_in, data, cmd);
        ret = fork();
        if (ret == 0)
        {
            argv = built_argv(cmd);
            envp = built_envp(data->env_vars);
            execve(find_binary_file(data, cmd->cmd_name), argv, envp);
            perror("execve error");
            _exit(1);
        }
        cmd = cmd->next;
    }
    dup2(tmp_in, STDIN);
    close(tmp_in);
    dup2(tmp_out, STDOUT);
    close(tmp_out);

    waitpid(ret, NULL, 0);
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
            {
                if (!execute_simple_cmd(data, pipeline->simple_cmd))
                    data->exit_status = 1;
            }
        }
        pipeline = pipeline->next;
    }
}
