/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:26:28 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/08 16:55:14 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_argv(t_list *list)
{
	if (list)
	{
		if (list->content)
			return (1 + count_argv(list->next));
		else
			return (count_argv(list->next));
	}
	return (0);
}

void	free_argv(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	fill_argv(char **argv, t_list *args)
{
	int		i;

	i = 0;
	while (args)
	{
		while (!(args->content))
			args = args->next;
		if (!(argv[i] = ft_strdup(args->content)))
		{
			free_argv(argv);
			argv = NULL;
			return ;
		}
		i++;
		args = args->next;
	}
	argv[i] = NULL;
}

char	**built_argv(t_command *cmd)
{
	char	**argv;
	int		argc;

	argc = 1 + count_argv(cmd->name_and_args);
	if (!(argv = (char **)malloc(argc * sizeof(char *))))
		return (NULL);
	ft_memset(argv, 0, argc * sizeof(char *));
	fill_argv(argv, cmd->name_and_args);
	return (argv);
}

int		args_num(char **args)
{
	int num;

	num = 0;
	if (!args)
		return (num);
	while (args[num])
		num++;
	return (num);
}
