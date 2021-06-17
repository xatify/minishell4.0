/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:25:50 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/07 12:11:23 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

BOOL	is_arg_alpha(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (i == 0 && s[i] == '-')
		{
			i++;
			continue;
		}
		if (i > 0 && s[i] == '-')
			return (TRUE);
		if (is_alpha(s[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		exit_(t_data *data, char **argv)
{
	int		status;
	int		ex;


	status = 0;
	ex = 0;
	if (argv[1] && argv[2])
	{
		ft_putstr_fd(MANY_ARGS, STDOUT);
		return (1);
	}
	if (argv[1])
	{
		status = ft_atoi(argv[1], &ex);
		if ((ex == 1 || is_arg_alpha(argv[1])) && (status = 255))
			ft_putstr_fd(NUM_ARG_R, STDERR);
	}
	if (data->in_terminal)
	{
		tputs(data->termc->keyend, 1, putchar_2);
		save_history(data);
	}
	free_data(data);
	free_argv(argv);
	exit(status);
}
