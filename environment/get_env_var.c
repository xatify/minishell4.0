/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:28:41 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 11:16:50 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_var(void *env_var)
{
	t_env_var	*var;

	var = (t_env_var *)env_var;
	free(var->name);
	free(var->value);
	free(var);
}

t_env_var	*create_env_var(char *name, char *value)
{
	t_env_var	*var;

	var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	return (var);
}

char	*get_env_name(char *name_value)
{
	char	*name;
	int		i;

	i = 0;
	while (name_value[i] && name_value[i] != '=')
		i++;
	name = (char *)malloc(i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, name_value, i);
	name[i] = '\0';
	return (name);
}

char	*get_env_value(char *name_value)
{
	char	*value;
	int		i;

	i = 0;
	while (name_value[i] && name_value[i] != '=')
		i++;
	if (name_value[i] == '\0')
		i--;
	value = ft_strdup(&name_value[i + 1]);
	return (value);
}
