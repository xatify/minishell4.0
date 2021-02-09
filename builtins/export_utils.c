/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:31:47 by keddib            #+#    #+#             */
/*   Updated: 2021/02/09 15:40:01 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	show_vars(t_data *data)
{
	int		i;
	char	**vars;

	vars = get_all_vars(data->env_vars, data->unset_vars);
	sort(vars);
	i = 0;
	while (vars[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(vars[i], STDOUT);
		ft_putstr_fd("\n", STDOUT);
		i++;
	}
	free_argv(vars);
}

BOOL	is_unset_var(t_list **unset_vars, char *name)
{
	t_list		*tmp;

	tmp = *(unset_vars);
	while (tmp)
	{
		if (ft_strcmp(tmp->content, name) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int		append_env_var(t_list **vars, char *var_name, char *new_value)
{
	t_env_var	*var;
	char		*tmp;

	var = search_var(vars, var_name);
	if (var)
	{
		if (!(tmp = ft_strjoin(var->value, new_value)))
			return (0);
		free(var->value);
		var->value = tmp;
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
