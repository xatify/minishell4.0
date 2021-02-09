/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:57:13 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/09 11:42:41 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_unset_var(t_list **unset_vars, char *name)
{
	t_list		*tmp;
	t_list		*last;

	last = NULL;
	tmp = *(unset_vars);
	while (tmp)
	{
		if (ft_strcmp(tmp->content, name) == 0)
		{
			if (tmp->next && last == NULL)
				(*unset_vars) = tmp->next;
			else if (tmp->next && last)
				last->next = tmp->next;
			else if (last == NULL)
				(*unset_vars) = NULL;
			else
				last->next = NULL;
			free(tmp->content);
			free(tmp);
			return ;
		}
		last = tmp;
		tmp = tmp->next;
	}
}

int		get_n_v(char *arg, char **name, char **value)
{
	int end;

	end = -1;
	*value = ft_strnstr(arg, "+=", &end);
	if (*value != NULL)
	{
		*value = ft_strdup(*value);
		*name = ft_substr(arg, 0, end);
	}
	else
	{
		*name = get_env_name(arg);
		*value = get_env_value(arg);
	}
	return (end);
}

int		not_identifier_name(char *arg)
{
	ft_putstr_fd("not a valid identifier ", 2);
	ft_putstr_fd(arg, 1);
	ft_putchar_fd('\n', 1);
	return (1);
}

int		hundle_var(t_data *data, char *arg, char **n_v, int e)
{
	if (*n_v[0] && is_identifier(n_v[0]))
	{
		if (ft_strchr(arg, '=') == NULL)
		{
			if (!search_var(&(data->env_vars), n_v[0]))
				if (!is_unset_var(&(data->unset_vars), n_v[1]))
					ft_lstadd_back(&(data->unset_vars),
									ft_lstnew(ft_strdup(n_v[0])));
		}
		else
		{
			if (is_double_quote_token(n_v[1]) || is_single_quote_token(n_v[1]))
				n_v[1] = remove_quotes(n_v[1]);
			if (is_unset_var(&(data->unset_vars), n_v[0]))
				remove_unset_var(&(data->unset_vars), n_v[0]);
			if (e != -1)
				append_env_var(&(data->env_vars), n_v[0], n_v[1]);
			else
				change_env_var(&(data->env_vars), n_v[0], n_v[1]);
		}
	}
	else
		return (not_identifier_name(arg));
	return (0);
}

int		export(char **args, t_data *data)
{
	char	*n_v[2];
	int		index;
	int		end;
	int		return_value;

	return_value = 0;
	index = 1;
	end = -1;
	if (!args[index])
		show_vars(data);
	while (args[index])
	{
		end = get_n_v(args[index], &(n_v[0]), &(n_v[1]));
		if (n_v[0])
		{
			return_value = hundle_var(data, args[index], n_v, end);
			free(n_v[0]);
		}
		if (n_v[1])
			free(n_v[1]);
		index++;
	}
	return (return_value);
}
