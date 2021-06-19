/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:04:51 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 19:21:29 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_shlv(t_env_var *var, char *envp)
{
	char	*tmp;

	if (ft_strcmp(var->name, "SHLVL") == 0)
	{
		tmp = get_env_value(envp);
		var->value = ft_itoa(ft_atoi(tmp, NULL) + 1);
		free(tmp);
	}
	else
		var->value = get_env_value(envp);
}

void	fill_envp(char **envp_i, t_env_var *var)
{
	int		name_len;

	name_len = ft_strlen(var->name);
	ft_strcpy(*envp_i, var->name);
	(*envp_i)[name_len] = '=';
	ft_strcpy((*envp_i) + name_len + 1, var->value);
}

t_list	*build_env_vars(char **envp)
{
	t_list		*list_head;
	t_env_var	*var;
	int			i;

	i = -1;
	list_head = NULL;
	while (envp[++i])
	{
		if (!creat_env(&list_head, envp[i]))
			return (NULL);
	}
	var = search_var(&list_head, "SHLVL");
	if (!var)
	{
		if (!creat_env(&list_head, NULL))
			return (NULL);
	}
	return (list_head);
}

char	**built_envp(t_list *vars)
{
	char		**envp;
	int			vars_num;
	int			i;

	vars_num = ft_lstsize(vars) + 1;
	envp = (char **)malloc(sizeof(char *) * vars_num);
	if (!envp)
		return (NULL);
	ft_memset(envp, 0, vars_num * sizeof(char *));
	i = 0;
	while (vars)
	{
		if (!create_envp(vars, envp, i))
			return (NULL);
		vars = vars->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

BOOL	creat_env(t_list **list_head, char *envp)
{
	t_env_var	*var;
	t_list		*new;

	var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!var)
	{
		ft_lstclear(list_head, free_env_var);
		return (0);
	}
	check_envp(envp, &var);
	new = ft_lstnew(var);
	if (!new)
	{
		free_env_var(var);
		ft_lstclear(list_head, free_env_var);
		return (0);
	}
	ft_lstadd_back(list_head, new);
	return (1);
}
