/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:18:25 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/29 10:30:05 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int	argc, char **argv, char **envp)
{
	t_data 	*data;
	char	*tmp;
	int 	ret;

	g_exit_status = 0;
	data = start_shell(argc, argv, envp);
	
	tmp = ft_strdup("");
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	while (TRUE)
	{
		signal(SIGINT, sig_int_handler);
		signal(SIGQUIT, sig_quit_handler);
		if (tmp[0] == '\0')
			ft_putstr_fd(PROMPT, 1);
		ret = get_next_line(0, &(data->input_cmd));
		data->input_cmd = ft_strjoin(tmp, data->input_cmd);
		if (ret == 1)
		{
			free(tmp);
			tmp = NULL;
			if (g_exit_status > 0)
			{
				data->exit_status = g_exit_status;
				g_exit_status = 0;
			}
			data->parse_tree = parser(data->input_cmd);
			if (!data->parse_tree)
				ft_putstr_fd("error while parsing\n", 2);
			else
				execute(data, data->parse_tree);
			tmp = ft_strdup("");
		}
		else if ((data->input_cmd)[0] == '\0')
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		else
			tmp = ft_strdup(data->input_cmd);
	}
	return (0);
}