/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/17 16:17:26 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		execute_built_in(char built_in, t_data *data, t_command *cmd)
{
	int		ret;
	char	**argv;
	int		fds[2];
	int		tmp_std[2];

	ft_memset(tmp_std, -1, 2);
	if (!redirect_std(cmd, fds))
		return (1);
	if (fds[0] != -1)
	{
		tmp_std[0] = dup(0);
		close(0);
		dup(fds[0]);
		close(fds[0]);
	}
	if (fds[1] != -1)
	{
		tmp_std[1] = dup(1);
		close(1);
		dup(fds[1]);
		close(fds[1]);
	}
	argv = built_argv(cmd);
	ret = 0;
	if (built_in == 'c')
		ret = cd(argv[1], data);
	else if (built_in == 'e')
		ret = echo_(argv);
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
	free_argv(argv);
	if (fds[0] != -1)
	{
		close(0);
		dup(tmp_std[0]);
		close(tmp_std[0]);
	}
	if (fds[1] != -1)
	{
		close(1);
		dup(tmp_std[1]);
		close(tmp_std[1]);
	}
	return (ret);
}

int		execute_child(t_data *data, t_command *cmd)
{
	char	*path;
	char	**argv;
	char	**envp;
	int		fds[2];

	if (!redirect_std(cmd, fds))
		return (1);
	if (fds[0] != -1)
	{
		close(0);
		dup(fds[0]);
		close(fds[0]);
	}
	if (fds[1] != -1)
	{
		close(1);
		dup(fds[1]);
		close(fds[1]);
	}
	path = find_binary_file(data, cmd->name_and_args->content);
	argv = built_argv(cmd);
	envp = built_envp(data->env_vars);
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

int		execve_error(char *path, char **argv, char **envp)
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

int		execute_binary(t_data *data, t_command *cmd)
{
	int		status;

	g_pid = fork();
	if (g_pid == 0)
		execute_child(data, cmd);
	else if (g_pid < 0)
		return (1);
	waitpid(g_pid, &status, 0);
	g_pid = -1;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

void	execute_simple_cmd(t_data *data, t_pipeline *pipeline)
{
	t_command	*cmd;
	char		*name_and_args;

	if ((cmd = (t_command *)(pipeline->cmds->content)))
	{
		name_and_args = cmd->name_and_args->content;
		cmd->built_in = is_built_in(name_and_args);
		if (cmd->built_in != '\0')
			data->exit_status = execute_built_in(cmd->built_in, data, cmd);
		else
			data->exit_status = execute_binary(data, cmd);
	}
}
