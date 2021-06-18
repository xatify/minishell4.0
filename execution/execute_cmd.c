/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 08:29:56 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		run_build_in(t_data *data, char	**argv, int *ret, t_command *cmd)
{
	*ret = 0;
	if (cmd->built_in == 'c')
		*ret = cd(argv[1], data);
	else if (cmd->built_in == 'e')
		*ret = echo_(argv);
	else if (cmd->built_in == 'n')
		*ret = env(argv[1], data->env_vars);
	else if (cmd->built_in == 'u')
		*ret = unset(argv, &(data->env_vars));
	else if (cmd->built_in == 'p')
		*ret = export(argv, data);
	else if (cmd->built_in == 'w')
		*ret = pwd(data);
	else
		*ret = exit_(data, argv);
	return (*ret);
}


int		execute_built_in(t_data *data, t_command *cmd)
{
	int		ret;
	char	**argv;
	int		tmp_std[2];

	if (simple_cmd_streaming(cmd, tmp_std))
		return (1);
	argv = built_argv(cmd);
	run_build_in(data, argv, &ret, cmd);
	free_argv(argv);
	if (tmp_std[0] != -1)
	{
		close(0);
		dup(tmp_std[0]);
		close(tmp_std[0]);
	}
	if (tmp_std[1] != -1)
	{
		close(1);
		dup(tmp_std[1]);
		close(tmp_std[1]);
	}
	return (ret);
}

int		execute_child(t_data *data, t_command *cmd, char **argv, char **envp)
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
	char	**argv;
	char	**envp;

	argv = built_argv(cmd);
	envp = built_envp(data->env_vars);
	g_pid = fork();
	if (g_pid == 0)
	{
		if(simple_cmd_streaming(cmd, NULL))
			exit(1);
		execute_child(data, cmd, argv, envp);
	}
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
	int			fds[2];

	if ((cmd = (t_command *)(pipeline->cmds->content)))
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
