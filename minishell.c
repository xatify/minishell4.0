/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:50:20 by abbouzid          #+#    #+#             */
/*   Updated: 2020/12/21 18:23:12 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main()
{
	char				*input_cmd;
	while (TRUE)
	{
		write(1, &PROMPT, ft_strlen(PROMPT));
		if (get_input(&input_cmd))
		{
			printf("%s\n", input_cmd);
			free(input_cmd);
			input_cmd = NULL;
		}
	}
}
