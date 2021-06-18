/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:07:27 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 11:17:39 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_var	*search_var(t_list **env_vars, char *var_name)
{
	t_env_var	*tmp;
	t_list		*list;

	list = (*env_vars);
	while (list)
	{
		tmp = (t_env_var *)(list->content);
		if (ft_strcmp(tmp->name, var_name) == 0)
			return (tmp);
		list = list->next;
	}
	return (NULL);
}

int	change_env_var(t_list **vars, char *var_name, char *new_value)
{
	t_env_var	*var;

	var = search_var(vars, var_name);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(new_value);
		if (!var->value)
			return (0);
	}
	else
	{
		var = create_env_var(var_name, new_value);
		if (var)
			ft_lstadd_back(vars, ft_lstnew(var));
		else
			return (0);
	}
	return (1);
}

void	del(t_list **vars, t_list *tmp, t_list *last)
{
	if (tmp->next)
	{
		if (last == NULL)
			(*vars) = tmp->next;
		else
			last->next = tmp->next;
	}
	else if (last == NULL)
		(*vars) = NULL;
	else
		last->next = NULL;
	ft_lstdelone(tmp, free_env_var);
}

void	del_env_var(t_list **vars, char *name)
{
	t_list		*tmp;
	t_list		*last;

	last = NULL;
	tmp = *(vars);
	while (tmp)
	{
		if (ft_strcmp(((t_env_var *)(tmp->content))->name, name) == 0)
		{
			del(vars, tmp, last);
			break ;
		}
		last = tmp;
		tmp = tmp->next;
	}
}
