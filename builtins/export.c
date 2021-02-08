/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:57:13 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/08 15:24:54 by keddib           ###   ########.fr       */
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
			if (tmp->next)
			{
				if (last == NULL)
					(*unset_vars) = tmp->next;
				else
					last->next = tmp->next;
			}
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

int		get_name_value(char *arg, char **name, char **value)
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

int		hundle_var(t_data *data, char *arg, char *n, char *v, int e)
{
	if (*n && is_identifier(n))
	{
		if (ft_strchr(arg, '=') == NULL)
		{
			if (!search_var(&(data->env_vars), n))
				if (!is_unset_var(&(data->unset_vars), n))
					ft_lstadd_back(&(data->unset_vars),
									ft_lstnew(ft_strdup(n)));
		}
		else
		{
			if (is_double_quote_token(v) || is_single_quote_token(v))
				v = remove_quotes(v);
			if (is_unset_var(&(data->unset_vars), n))
				remove_unset_var(&(data->unset_vars), n);
			if (e != -1)
				append_env_var(&(data->env_vars), n, v);
			else
				change_env_var(&(data->env_vars), n, v);
		}
	}
	else
		return (not_identifier_name(arg));
	return (0);
}

int		export(char **args, t_data *data)
{
	char	*name;
	char	*value;
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
		end = get_name_value(args[index], &name, &value);
		if (name)
		{
			return_value = hundle_var(data, args[index], name, value, end);
			free(name);
		}
		if (value)
			free(value);
		index++;
	}
	return (return_value);
}
