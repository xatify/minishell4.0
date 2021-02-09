/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/09 16:38:27 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		execute_built_in(char built_in, t_data *data, t_command *cmd)
{
	int		ret;
	char	**argv;

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
	free_argv(argv);
	return (ret);
}

int		execute_child(t_data *data, t_command *cmd)
{
	char	*path;
	char	**argv;
	char	**envp;

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
	int			save_std[2];
	int			tmp_fd[2];
	char		*name_and_args;

	save_std[0] = dup(STDIN);
	save_std[1] = dup(STDOUT);
	if ((cmd = (t_command *)(pipeline->cmds->content)))
	{
		if (!simple_cmd_file_redirection(cmd, save_std, tmp_fd))
		{
			data->exit_status = 1;
			return ;
		}
		name_and_args = cmd->name_and_args->content;
		cmd->built_in = is_built_in(name_and_args);
		if (cmd->built_in != '\0')
			data->exit_status = execute_built_in(cmd->built_in, data, cmd);
		else
			data->exit_status = execute_binary(data, cmd);
	}
	set_to_std(save_std);
}
