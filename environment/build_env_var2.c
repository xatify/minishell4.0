/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env_var2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:15:34 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 19:21:48 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_envp(t_list *vars, char **envp, int i)
{
	t_env_var	*var;

	var = (t_env_var *)(vars->content);
	envp[i] = (char *)malloc(ft_strlen(var->name) + ft_strlen(var->value) + 2);
	if (!envp[i])
	{
		free_argv(envp);
		return (0);
	}
	fill_envp(&(envp[i]), var);
	return (1);
}

void	check_envp(char *envp, t_env_var **var)
{
	if (envp)
	{
		(*var)->name = get_env_name(envp);
		change_shlv(*var, envp);
	}
	else
	{
		(*var)->name = ft_strdup("SHLVL");
		(*var)->value = ft_strdup("1");
	}
}
