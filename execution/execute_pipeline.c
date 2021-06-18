/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:25:28 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 18:30:40 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_std_stream(int std, int fd)
{
	close(std);
	dup(fd);
	close(fd);
}

void	first_child(t_command *cmd, int *pipe_fds, int *file_fds)
{
	if (!redirect_std(cmd, file_fds))
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exit(1);
	}
	if (file_fds[0] != -1)
		set_std_stream(0, file_fds[0]);
	if (file_fds[1] != -1)
	{
		set_std_stream(1, file_fds[1]);
		close(pipe_fds[1]);
	}
	else
		set_std_stream(1, pipe_fds[1]);
	close(pipe_fds[0]);
}

void	middle_child(t_command *cmd, int *pipe_fds, int *file_fds, int in_tmp)
{
	if (!redirect_std(cmd, file_fds))
	{
		close(in_tmp);
		close(pipe_fds[1]);
		exit(1);
	}
	if (file_fds[0] != -1)
	{
		close(in_tmp);
		set_std_stream(0, file_fds[0]);
	}
	else
		set_std_stream(0, in_tmp);
	if (file_fds[1] != -1)
	{
		close(pipe_fds[1]);
		set_std_stream(1, file_fds[1]);
	}
	else
		set_std_stream(1, pipe_fds[1]);
}

void	last_child(t_command *cmd, int *file_fds, int in_tmp)
{
	if (!redirect_std(cmd, file_fds))
	{
		close(in_tmp);
		exit(1);
	}
	if (file_fds[0] != -1)
	{
		close(in_tmp);
		set_std_stream(0, file_fds[0]);
	}
	else
		set_std_stream(0, in_tmp);
	if (file_fds[1] != -1)
		set_std_stream(1, file_fds[1]);
}

void	piping_to_child(t_command *cmd, int *pipe_fd, t_list *cmds,
		int index_in_tmp[2])
{
	int		file_fds[2];

	file_fds[0] = -1;
	file_fds[1] = -1;
	if (index_in_tmp[0] == 0)
		first_child(cmd, pipe_fd, file_fds);
	else if (cmds->next)
		middle_child(cmd, pipe_fd, file_fds, index_in_tmp[1]);
	else
		last_child(cmd, file_fds, index_in_tmp[1]);
}

void	run_child_pipe(t_list *cmds, int *pipe_fds, int index_in_tmp[2],
						t_data *data)
{
	t_command	*cmd;
	char		**argv;
	char		**envp;
	int			ret;

	cmd = (t_command *)(cmds->content);
	piping_to_child(cmd, pipe_fds, cmds, index_in_tmp);
	if (cmd->name_and_args)
	{
		cmd->built_in = is_built_in(cmd->name_and_args);
		argv = built_argv(cmd);
		envp = built_envp(data->env_vars);
		if (cmd->built_in != '\0')
			exit(run_build_in(data, argv, &ret, cmd));
		else
			execute_child(data, cmd, argv, envp);
	}
	else
		exit(0);
}

void	wait_children(t_data *data, int i)
{
	int		status;

	if (waitpid(g_pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		g_pid = 0;
	}
	i--;
	while (i)
	{
		if (waitpid(-1, &status, 0) > 0)
			i--;
	}
}

void	execute_pipeline(t_data *data, t_list *cmds)
{
	int			pipe_fds[2];
	int			index_in_tmp[2];

	index_in_tmp[0] = 0;
	index_in_tmp[1] = -1;
	while (cmds)
	{
		if (cmds->next)
			if (pipe(pipe_fds) == -1)
				exit(1);
		g_pid = fork();
		if (g_pid == 0)
			run_child_pipe(cmds, pipe_fds, index_in_tmp, data);
		else if (g_pid > 0)
		{
			if (index_in_tmp[1] != -1)
				close(index_in_tmp[1]);
			index_in_tmp[1] = pipe_fds[0];
			close(pipe_fds[1]);
		}
		else
			exit(1);
		cmds = cmds->next;
		index_in_tmp[0]++;
	}
	wait_children(data, index_in_tmp[0]);
}

void	execute(t_data *data)
{
	t_list		*pipelines;
	t_pipeline	*pipeline;

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
		else
			data->exit_status = 1;
		pipelines = pipelines->next;
	}
}
