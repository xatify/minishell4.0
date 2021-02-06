/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:59:19 by keddib            #+#    #+#             */
/*   Updated: 2021/02/05 15:37:41 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char    *search_files_inpath(char *path, char *cmd_name)
{
	struct  dirent  *dir;
	DIR             *d;

	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strcmp(dir->d_name, cmd_name) == 0)
			{
				closedir(d);
				return (path);
			}
		}
		closedir(d);
	}
	return(NULL);
}

char    *absolute_path(char *cmd_name, char *path_env)
{
	char    **paths;
	char    *final_path;
	int     i;

	if (ft_strchr(cmd_name, '/'))
		return cmd_name;
	paths = ft_split(path_env, ':');
	i  = 0;
	while (paths[i])
	{
		if (search_files_inpath(paths[i], cmd_name) != NULL)
		{
			paths[i]= ft_strjoin(paths[i], "/");
			final_path= ft_strjoin(paths[i], cmd_name);
			//free array
			return (final_path);
		}
		i++;
	}
	return NULL;
}

char    *find_binary_file(t_data *data, char *cmd_name)
{
	char    *bins_dirs;
	char    *path;

	bins_dirs = get_bins_path(data);
	if (!bins_dirs)
		return (NULL);
	path = absolute_path(cmd_name, bins_dirs);
	return (path);
}

char    *get_bins_path(t_data *data)
{
	t_env_var      *bins_path;

	bins_path = search_var(&(data->env_vars), "PATH");
	if (!bins_path)
		return (NULL);
	return (bins_path->value);
}
