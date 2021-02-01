/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:12:56 by keddib            #+#    #+#             */
/*   Updated: 2021/02/01 14:41:53 by abbouzid         ###   ########.fr       */
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

int					get_vars_len(t_list *env_vars, t_list *unset_vars)
{
	return (ft_lstsize(env_vars) + ft_lstsize(unset_vars));
}


char 				**get_all_vars(t_list *env_vars, t_list *unset_vars)
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
		first = ft_strjoin(((t_env_var *)(env_vars->content))->name, "=\"");
		second = ft_strjoin(((t_env_var *)(env_vars->content))->value, "\"");
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
		if (!(holder[i++] = ft_strdup(unset_vars->content)))
		{
			free_argv(holder);
			return (NULL);
		}
		unset_vars = unset_vars->next;
	}
	holder[i] = NULL;
	return (holder);
}
