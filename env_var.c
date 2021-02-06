/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:28:41 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/06 18:20:39 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void		free_env_var(void *env_var)
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

	if (!(var = (t_env_var *)malloc(sizeof(t_env_var))))
		return (NULL);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	return (var);
}

void		change_shlv(t_env_var *var, char *envp)
{
	char *tmp;

	if (ft_strcmp(var->name, "SHLVL") == 0)
	{
		tmp = get_env_value(envp);
		var->value = ft_itoa(ft_atoi(tmp, NULL) + 1);
		free(tmp);
	}
	else
		var->value = get_env_value(envp);
}

t_list		*build_env_vars(char **envp)
{
	t_list		*list_head;
	t_list		*new;
	t_env_var	*var;
	int			i;

	i = -1;
	list_head = NULL;
	while (envp[++i])
	{
		if (!(var = (t_env_var *)malloc(sizeof(t_env_var))))
		{
			ft_lstclear(&list_head, free_env_var);
			return (NULL);
		}
		var->name = get_env_name(envp[i]);
		change_shlv(var, envp[i]);
		if (!(new = ft_lstnew(var)))
		{
			free_env_var(var);
			ft_lstclear(&list_head, free_env_var);
			return (NULL);
		}
		ft_lstadd_back(&list_head, new);
	}
	return (list_head);
}

char		*get_env_name(char *name_value)
{
	char	*name;
	int		i;

	i = 0;
	while (name_value[i] && name_value[i] != '=')
		i++;
	if (!(name = (char *)malloc(i + 1)))
		return (NULL);
	ft_strlcpy(name, name_value, i);
	name[i] = '\0';
	return (name);
}

char    *get_env_value(char *name_value)
{
	char    *value;
	int     i;

	i = 0;
	while (name_value[i] && name_value[i] != '=')
		i++;
	if (name_value[i] == '\0')
		i--;

	value = ft_strdup(&name_value[i + 1]);
	return (value);
}

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

int			change_env_var(t_list **vars, char *var_name, char *new_value)
{
	t_env_var	*var;

	var = search_var(vars, var_name);
	if (var)
	{
		free(var->value);
		if (!(var->value = ft_strdup(new_value)))
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

void		fill_envp(char **envp_i, t_env_var *var)
{
	int     name_len;

	name_len = ft_strlen(var->name);
	ft_strcpy(*envp_i, var->name);
	(*envp_i)[name_len] = '=';
	ft_strcpy((*envp_i) + name_len + 1, var->value);
}


char		**built_envp(t_list *vars)
{
	char		**envp;
	int			vars_num;
	t_env_var	*var;
	int			i;

	vars_num = ft_lstsize(vars) + 1;
	if (!(envp = (char **)malloc(sizeof(char *) * vars_num)))
		return (NULL);
	ft_memset(envp, 0, vars_num * sizeof(char *));
	i = 0;
	while (vars)
	{
		var = (t_env_var *)(vars->content);
		if (!(envp[i] = (char *)malloc(ft_strlen(var->name) +
						ft_strlen(var->value) + 2)))
		{
			free_argv(envp);
			return (NULL);
		}
		fill_envp(&(envp[i]), var);
		vars = vars->next;
		i++;
	}
	envp[i] = NULL;
	return(envp);
}

void 		del(t_list **vars, t_list *tmp, t_list *last)
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

void		del_env_var(t_list **vars, char *name)
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
