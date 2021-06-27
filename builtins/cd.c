/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:29:16 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 11:03:32 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**  change corrent directory to path if path is not null otherwise to $HOME
*/

int	hundle_removed_path(char *path, t_list **vars, t_data *data)
{
	t_env_var	*var_env;
	char		*tmp;
	int			i;

	i = 0;
	while (path[i])
		i++;
	var_env = search_var(&(data->env_vars), "PWD");
	if (var_env)
	{
		tmp = path;
		if (path[--i] != '/')
			tmp = ft_strjoin("/", path);
		change_env_var(vars, "OLDPWD", var_env->value);
		change_env_var(vars, "PWD", ft_strjoin(var_env->value, tmp));
	}
	ft_putstr_fd(RM_PATH, STDERR);
	return (0);
}

void	hundle_exicted_path(t_data *data, char *pwd)
{
	t_env_var	*var_env;

	if (pwd)
		change_env_var(&(data->env_vars), "OLDPWD", pwd);
	else
	{
		var_env = search_var(&(data->env_vars), "PWD");
		if (var_env)
			change_env_var(&(data->env_vars), "OLDPWD", var_env->value);
	}
	free(pwd);
	pwd = getcwd(NULL, 0);
	change_env_var(&(data->env_vars), "PWD", pwd);
}

int	cd(char *path, t_data *data)
{
	char		*dir;
	int			ret;
	char		*pwd;
	t_env_var	*var_env;

	if (path)
		dir = ft_strdup(path);
	else
	{
		var_env = search_var(&(data->env_vars), "HOME");
		dir = ft_strdup(var_env->value);
	}
	pwd = getcwd(NULL, 0);
	ret = chdir(dir);
	free(dir);
	dir = NULL;
	dir = getcwd(NULL, 0);
	if (!ret && (pwd || dir))
		hundle_exicted_path(data, pwd);
	else if (!pwd && !ret)
		return (hundle_removed_path(path, &(data->env_vars), data));
	else
	{
		free(pwd);
		free(dir);
		ft_putstr_fd(NO_F_D, STDERR);
		return (1);
	}
	free(pwd);
	free(dir);
	return (ret);
}
