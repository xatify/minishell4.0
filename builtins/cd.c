/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:29:16 by abbouzid          #+#    #+#             */
/*   Updated: 2021/07/02 18:56:07 by keddib           ###   ########.fr       */
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

void	hundle_exicted_path(t_data *data, char **pwd)
{
	t_env_var	*var_env;

	if (*pwd)
		change_env_var(&(data->env_vars), "OLDPWD", *pwd);
	else
	{
		var_env = search_var(&(data->env_vars), "PWD");
		if (var_env)
			change_env_var(&(data->env_vars), "OLDPWD", var_env->value);
	}
	free(*pwd);
	*pwd = getcwd(NULL, 0);
	change_env_var(&(data->env_vars), "PWD", *pwd);
}

int	cd_pwd(char *path, char **pwd, char **dir, t_data *data)
{
	int			ret;
	t_env_var	*var_env;

	var_env = search_var(&(data->env_vars), "HOME");
	if (var_env)
		*dir = ft_strdup(var_env->value);
	if (path)
	{
		free(*dir);
		*dir = NULL;
		*dir = ft_strdup(path);
	}
	*pwd = getcwd(NULL, 0);
	ret = chdir(*dir);
	free(*dir);
	*dir = NULL;
	*dir = getcwd(NULL, 0);
	return (ret);
}

int	cd(char *path, t_data *data)
{
	char		*dir;
	int			ret;
	char		*pwd;

	dir = NULL;
	pwd = NULL;
	ret = cd_pwd(path, &pwd, &dir, data);
	if (!ret && (pwd || dir))
		hundle_exicted_path(data, &pwd);
	else if (!pwd && !ret)
		return (hundle_removed_path(path, &(data->env_vars), data));
	else
	{
		ft_putstr_fd(NO_F_D, STDERR);
		ret = 1;
	}
	free(pwd);
	free(dir);
	return (ret);
}
