/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 01:59:14 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/03 15:43:06 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		get_input(char **buffer)
{
	int		len_buffer;
	int		ret;
	char	tmp_buffer;
	char	*ptr;

	*buffer = NULL;
	tmp_buffer = '\0';
	while((ret = read(STDIN, &tmp_buffer, 1)) >= 0)
	{
		if (ret == 1 && tmp_buffer != '\n')
		{
			len_buffer = ft_strlen(*buffer);
			ptr = *buffer;
			if ((*buffer = malloc(len_buffer + 2)) == NULL)
			{
				if (ptr != NULL)
					free(ptr);
				return (0);
			}
			ft_strcpy(*buffer, ptr);
			(*buffer)[len_buffer] = tmp_buffer;
			(*buffer)[len_buffer + 1] = '\0';
			if (ptr)
				free(ptr);
			ptr = NULL;
		}
		else
		{
			if (!(*buffer))
				(*buffer) = ft_strdup("");
			return (1);
		}
	}
	return (0);
}


