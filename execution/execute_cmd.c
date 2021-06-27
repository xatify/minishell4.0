/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/27 15:36:16 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_child(t_data *data, t_command *cmd, char **argv, char **envp)
{
	char	*path;

	path = find_binary_file(data, cmd->name_and_args->content);
	if (!path)
	{
		ft_putstr_fd("no such file or directory : ", STDERR);
		ft_putstr_fd(cmd->name_and_args->content, STDERR);
		ft_putstr_fd("\n", STDERR);
		exit(127);
	}
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(path, argv, envp);
	exit(execve_error(path, argv, envp));
}

int	execve_error(char *path, char **argv, char **envp)
{
	free(path);
	free_argv(argv);
	free_argv(envp);
	if (errno == 8)
		return (0);
	else if (errno == 13)
		ft_putstr_fd(P_DENIED, STDERR);
	else
		ft_putstr_fd(NO_F_D, STDERR);
	return (126);
}

int	execute_binary(t_data *data, t_command *cmd)
{
	int		status;
	char	**argv;
	char	**envp;

	g_pid = fork();
	if (g_pid == 0)
	{
		argv = built_argv(cmd);
		envp = built_envp(data->env_vars);
		if (simple_cmd_streaming(cmd, NULL))
			exit(1);
		execute_child(data, cmd, argv, envp);
	}
	else if (g_pid < 0)
		return (1);
	waitpid(g_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

void	execute_simple_cmd(t_data *data, t_pipeline *pipeline)
{
	t_command	*cmd;
	int			fds[2];

	cmd = (t_command *)(pipeline->cmds->content);
	if (cmd)
	{
		if (cmd->name_and_args)
		{
			cmd->built_in = is_built_in(cmd->name_and_args);
			if (cmd->built_in != '\0')
				data->exit_status = execute_built_in(data, cmd);
			else
				data->exit_status = execute_binary(data, cmd);
		}
		else
		{
			data->exit_status = !redirect_std(cmd, fds);
			if (fds[0] != -1)
				close(fds[0]);
			if (fds[1] != -1)
				close(fds[1]);
		}
	}
}
