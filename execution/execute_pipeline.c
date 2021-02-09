/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:25:28 by keddib            #+#    #+#             */
/*   Updated: 2021/02/09 11:06:51 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	return_status(int status, t_data *data)
{
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else
		data->exit_status = status;
}

void	execute_pipe(t_command *cmd, t_data *data)
{
	char	*name_and_args;

	if (!cmd->name_and_args)
		return ;
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

void	execute_pipeline(t_data *data, t_list *cmds)
{
	int			tmp_fd[2];
	int			save_std[2];
	int			status;
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
		execute_pipe(cmd, data);
		cmds = cmds->next;
	}
	waitpid(g_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	set_to_std(save_std);
	g_pid = -1;
	return_status(status, data);
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
