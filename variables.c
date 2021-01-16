/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:12:56 by keddib            #+#    #+#             */
/*   Updated: 2021/01/16 10:19:32 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*remove_quotes(char *value)
{
	char	*unquoted;
	int		i;

	i = ft_strlen(value) - 1;
	if (value[0] == value[i] && (value[0] == 0x27 || value[0] == 0x22))
	{
		if (!(unquoted = malloc(ft_strlen(value))))
			return (NULL);
		ft_strlcpy(unquoted, value + 1, i - 1);
		free(value);
		return (unquoted);
	}
	return (value);
}

int					get_vars_len(t_env_vars *env_vars, t_strlist *unset_vars)
{
	int		len;

	len = 0;
	while(env_vars != NULL)
    {
		len++;
        env_vars = env_vars->next;
    }
	while(unset_vars != NULL)
	{
		len++;
		unset_vars = unset_vars->next;
	}
	return len;
}


char 				**get_all_vars(t_env_vars *env_vars, t_strlist *unset_vars)
{
	int		len;
	int		i;
	char	**holder;
	char	*first;
	char	*second;

	len = get_vars_len(env_vars, unset_vars);
	if (!(holder = malloc((len + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (env_vars != NULL)
	{
		first = ft_strjoin(env_vars->name, "=\"");
		second = ft_strjoin(env_vars->value, "\"");
		if (!(holder[i++] = ft_strjoin(first, second)))
		{
			free_argv(holder);
			return (NULL);
		}
		env_vars = env_vars->next;
		free(first);
		free(second);
	}
	while (unset_vars != NULL)
	{
		if (!(holder[i++] = ft_strdup(unset_vars->str)))
		{
			free_argv(holder);
			return (NULL);
		}
		unset_vars = unset_vars->next;
	}
	holder[i] = NULL;
	return (holder);
}
