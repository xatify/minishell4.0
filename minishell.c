/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:18:25 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/06 13:59:24 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*holder;

	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	data = start_shell(argc, argv, envp, &holder);
	if (data->in_terminal)
		build_history(data);
	while (TRUE)
	{
		new_input(data, &holder);
		ft_lstclear(&(data->parse_tree), free_pipeline);
	}
	return (0);
}
