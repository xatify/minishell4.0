/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:28:43 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/03 19:10:10 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		free_data(t_data *data)
{
	ft_lstclear(&(data->env_vars), free_env_var);
	ft_lstclear(&(data->unset_vars), free);
	ft_lstclear(&(data->parse_tree), free_pipeline);
	if (data->input_cmd)
		free(data->input_cmd);
	free(data);
}

void		set_non_canonocal_mode(t_data *data)
{
	if(isatty(STDIN))
	{
		data->in_terminal = 1;
		tcgetattr(STDIN, &data->origin);
		tcgetattr(STDIN, &data->modified);
		data->modified.c_lflag &= ~(ICANON);
		//data->origin.c_lflag &= ~(ECHOCTL);
		data->modified.c_lflag &= ~(ECHO);
		data->modified.c_cc[VMIN] = 1;
		data->modified.c_cc[VTIME] = 0;
	}
}

t_data		*start_shell(int argc, char **argv, char **envp, char **holder)
{
	t_data		*data;

	argc = 0;
	argv = NULL;
	if (!(data = (t_data *)malloc(sizeof(t_data))))
		exit(1);
	ft_memset(data, 0, sizeof(t_data));
	set_non_canonocal_mode(data);
	if (!(data->env_vars = build_env_vars(envp)) || !(*holder = ft_strdup("")))
	{
		free_data(data);
		exit(1);
	}
	return (data);
}
