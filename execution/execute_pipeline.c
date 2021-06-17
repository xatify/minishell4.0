/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:25:28 by keddib            #+#    #+#             */
/*   Updated: 2021/06/17 16:14:16 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		no_cmd(t_data *data, int *save_std)
{
	data->exit_status = 0;
	set_to_std(save_std);
	return (1);
}

void	return_status(int *save_std, int *tmp_fd, t_data *data)
{
	int		status;
	//int ret;

	if (data->no_status_check == 0)
		waitpid(g_pid, &status, 0);
	else
		status = 0;
	//while (wait(NULL) > 0)
	//;
	while (waitpid(-1, NULL, 0) > 0)
	;
	close(tmp_fd[0]);
	close(tmp_fd[1]);
	set_to_std(save_std);
	g_pid = -1;
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else
		data->exit_status = status;
}

void	execute_pipe(t_command *cmd, t_data *data)
{
	char	*name_and_args;

	name_and_args = cmd->name_and_args->content;
	cmd->built_in = is_built_in(name_and_args);
	if (cmd->built_in != '\0' && ft_strcmp(name_and_args, "cd") != 0 && ft_strcmp(name_and_args, "exit") != 0)
		data->exit_status = execute_built_in(cmd->built_in, data, cmd);
	else
	{
		g_pid = fork();
		if (g_pid == 0)
		{
			if (ft_strcmp(name_and_args, "exit") == 0)
				data->exit_status = execute_built_in(cmd->built_in, data, cmd);
			else
				execute_child(data, cmd);
		}
		else if (g_pid < 0)
			data->exit_status = 1;
	}
}

void	execute_pipeline(t_data *data, t_list *cmds)
{
	int			tmp_fd[2];
	int			save_std[2];
	t_command	*cmd;

	set_fds(save_std, tmp_fd);
	while (cmds)
	{
		cmd = (t_command *)(cmds->content);
		if (!pipeline_stream(cmd, save_std, tmp_fd, cmds))
		{
			cmds = cmds->next;
			continue;
		}
		if (!cmd->name_and_args && cmds->next)
		{
			cmds = cmds->next;
			continue;
		}
		if (!cmd->name_and_args && !cmds->next)
			data->no_status_check = 1;
		else
			execute_pipe(cmd, data);
		cmds = cmds->next;
	}
	return_status(save_std, tmp_fd ,data);
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
