/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:28:43 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/06 09:41:22 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_data  *start_shell(int argc, char **argv, char **envp, char **holder)
{
	t_data  *data;
	struct stat st;

	argc = 0;
	argv = NULL;
	g_reading = 0;
	fstat(STDIN, &st);
	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	if (!S_ISCHR(st.st_mode))
		data->input_from_file = 1;
	data->env_vars = build_env_vars(envp);
	if (!data->env_vars)
	{
		free(data);
		exit(1);
	}
	*holder = ft_strdup("");
	if (!(*holder))
	{
		free_data(data);
		exit(1);
	}
	return (data);
}

void    free_data(t_data *data)
{
	ft_lstclear(&(data->env_vars), free_env_var);
	ft_lstclear(&(data->unset_vars), free);
	ft_lstclear(&(data->parse_tree), free_pipeline);
	if (data->input_cmd)
		free(data->input_cmd);
}

void    set_input_cmd(t_data *data, char **holder)
{
	char *tmp;

	tmp = data->input_cmd;
	data->input_cmd = ft_strjoin(*holder, data->input_cmd);
	free(*holder);
	free(tmp);
}

void    handl_signals_exit_status(t_data *data)
{
	if (g_exit_status > 0)
	{
		data->exit_status = g_exit_status;
		g_exit_status = 0;
	}
}


void    new_input(t_data *data, char **holder)
{
	int ret;

	data->input_cmd = NULL;
	if (**holder == '\0' && !data->input_from_file)
			ft_putstr_fd(PROMPT, 1);
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	ret = get_next_line(0, &(data->input_cmd));
	set_input_cmd(data, holder);
	if (ret == 1 || (ret == 0 && (data->input_cmd[0] != '\0') && data->input_from_file))
	{
		handl_signals_exit_status(data);
		if (data->input_cmd[0] != '\0')
		{
			if (!(data->parse_tree = parser(data->input_cmd)))
				ft_putstr_fd("error while parsing\n", 2);
			else
				execute(data);
		}
		*holder = ft_strdup("");
		free(data->input_cmd);
	}
	else if (ret == 0 && (data->input_cmd[0] == '\0'))
	{
		if (!data->input_from_file)
			ft_putstr_fd("exit\n", 1);
		free_data(data);
		exit(0);
	}
	else if (!data->input_from_file)
		*holder = ft_strdup(data->input_cmd);
}
