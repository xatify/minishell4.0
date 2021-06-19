/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:28:43 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/19 08:18:46 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_data *data)
{
	ft_lstclear(&(data->env_vars), free_env_var);
	ft_lstclear(&(data->unset_vars), free);
	ft_lstclear(&(data->parse_tree), free_pipeline);
	ft_lstclear(&(data->history_head), free);
	free(data->termc);
	free(data->input_cmd);
	free(data);
}

BOOL	check_termc(t_data *data)
{
	data->termc->keystart = tgetstr("ks", 0);
	if (!data->termc->keystart)
		return (FALSE);
	data->termc->clear_line = tgetstr("dl", 0);
	if (!data->termc->clear_line)
		return (FALSE);
	data->termc->up_key = tgetstr("ku", 0);
	if (!data->termc->up_key)
		return (FALSE);
	data->termc->down_key = tgetstr("kd", 0);
	if (!data->termc->down_key)
		return (FALSE);
	data->termc->cariage_return = tgetstr("cr", 0);
	if (!data->termc->cariage_return)
		return (FALSE);
	data->termc->keyend = tgetstr("ke", 0);
	if (!data->termc->keyend)
		return (FALSE);
	return (TRUE);
}

BOOL	set_non_canonocal_mode(t_data *data)
{
	char	*termtype;
	int		i;

	if (isatty(STDIN))
	{
		termtype = getenv("TERM");
		if (!termtype)
			exit(1);
		i = tgetent(0, termtype);
		if (i != 1)
			return (FALSE);
		data->termc = malloc(sizeof(t_termc));
		if (!data->termc)
			return (FALSE);
		ft_memset((data->termc), 0, sizeof(t_termc));
		data->in_terminal = 1;
		tcgetattr(STDIN, &data->origin);
		tcgetattr(STDIN, &data->modified);
		data->modified.c_lflag &= ~(ICANON);
		data->modified.c_lflag &= ~(ECHO);
		data->modified.c_cc[VMIN] = 0;
		data->modified.c_cc[VTIME] = 0;
		if (!check_termc(data))
			return (FALSE);
		data->in_terminal = 1;
	}
	return (TRUE);
}

t_data	*start_shell(int argc, char **argv, char **envp, char **holder)
{
	t_data		*data;

	argc = 0;
	argv = NULL;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	ft_memset(data, 0, sizeof(t_data));
	if (!set_non_canonocal_mode(data))
	{
		free_data(data);
		exit(1);
	}
	data->env_vars = build_env_vars(envp);
	*holder = ft_strdup("");
	if (!data->env_vars || !*holder)
	{
		free_data(data);
		exit(1);
	}
	g_pid = 0;
	return (data);
}
