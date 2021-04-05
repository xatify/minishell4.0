/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:28:43 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/05 17:12:55 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		free_data(t_data *data)
{
	ft_lstclear(&(data->env_vars), free_env_var);
	ft_lstclear(&(data->unset_vars), free);
	ft_lstclear(&(data->parse_tree), free_pipeline);
	if (data->input_cmd)
		free(data->input_cmd);
	free(data);
}

BOOL		set_non_canonocal_mode(t_data *data)
{
	if(isatty(STDIN))
	{
		if (!(data->termtype = getenv("TERM")) || tgetent(0, data->termtype) != 1)
			return (FALSE);
		data->in_terminal = 1;
		tcgetattr(STDIN, &data->origin);
		tcgetattr(STDIN, &data->modified);
		data->modified.c_lflag &= ~(ICANON);
		data->modified.c_lflag &= ~(ECHO);
		data->modified.c_cc[VMIN] = 0;
		data->modified.c_cc[VTIME] = 0;
		if (!(data->termc = malloc(sizeof(t_termc))))
			return (FALSE);
		ft_memset(data->termc, 0, sizeof(t_termc));
		char *tmp;

		if (!(tmp = tgetstr("ks", 0)))
		{
			printf("not present");
			exit(1);
		}
		tputs(tmp, 1, putchar_2);
		if (!(data->termc->clear_line = tgetstr("dl", 0))
			|| !(data->termc->erase = tgetstr("dc", 0))
			|| !(data->termc->left_key = tgetstr("le", 0))
			|| !(data->termc->right_key = tgetstr("nd", 0))
			|| !(data->termc->up_key = tgetstr("ku", 0))
			|| !(data->termc->down_key = tgetstr("kd", 0))
			|| !(data->termc->cariage_return = tgetstr("cr", 0)))
			return (FALSE);

	}
	return (TRUE);
}

t_data		*start_shell(int argc, char **argv, char **envp, char **holder)
{
	t_data		*data;

	argc = 0;
	argv = NULL;
	if (!(data = (t_data *)malloc(sizeof(t_data))))
		exit(1);
	ft_memset(data, 0, sizeof(t_data));
	if (!set_non_canonocal_mode(data))
	{
		///// free_data needs checking for unfreed pointer
		free_data(data);
		exit(1);
	}
	if (!(data->env_vars = build_env_vars(envp)) || !(*holder = ft_strdup("")))
	{
		free_data(data);
		exit(1);
	}
	return (data);
}
