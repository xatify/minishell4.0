/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:28:43 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/27 15:42:12 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_data *data)
{
	ft_lstclear(&(data->env_vars), free_env_var);
	ft_lstclear(&(data->unset_vars), free);
	ft_lstclear(&(data->parse_tree), free_pipeline);
	free(data->input_cmd);
}

void	start_shell(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->env_vars = build_env_vars(envp);
	if (!data->env_vars)
	{
		free_data(data);
		exit(1);
	}
	g_pid = 0;
}
