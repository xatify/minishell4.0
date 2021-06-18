/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:23:12 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 11:23:30 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_build_in(t_data *data, char	**argv, int *ret, t_command *cmd)
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

int	execute_built_in(t_data *data, t_command *cmd)
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
