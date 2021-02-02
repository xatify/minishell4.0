/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:18:25 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/02 16:16:00 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int	argc, char **argv, char **envp)
{
	t_data 	*data;
	char	*holder;

	data = start_shell(argc, argv, envp);
	holder = ft_strdup("");
	if (!holder)
	{
		free_data(data);
		exit(1);
	}
	while (TRUE)
	{
		signal(SIGINT, sig_int_handler);
		signal(SIGQUIT, sig_quit_handler);
		new_input(data, &holder);
		ft_lstclear(&(data->parse_tree), free_pipeline);
	}
	return (0);
}