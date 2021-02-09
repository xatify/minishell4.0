/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:28:43 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/09 08:54:49 by abbouzid         ###   ########.fr       */
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

t_data		*start_shell(int argc, char **argv, char **envp, char **holder)
{
	t_data		*data;
	struct stat	st;

	argc = 0;
	argv = NULL;
	fstat(STDIN, &st);
	if (!(data = (t_data *)malloc(sizeof(t_data))))
		exit(1);
	ft_memset(data, 0, sizeof(t_data));
	if (!S_ISCHR(st.st_mode))
		data->input_from_file = 1;
	data->env_vars = build_env_vars(envp);
	if (!data->env_vars)
	{
		free_data(data);
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
