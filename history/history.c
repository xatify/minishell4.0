/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:08:34 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/04 19:16:09 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_history(t_list **hist_head, t_list **hist_index, char *command)
{
	t_list		*new = NULL;

	if (*command)
	{
		if (((*hist_head) && ft_strcmp((*hist_head)->content, command)) ||
			!(*hist_head))
			new = ft_lstnew(ft_strdup(command));
		if (new)
		{
			if (!(*hist_head))
				*hist_head = new;
			else
			{
				new->next = *hist_head;
				(*hist_head)->previous = new;
				*hist_head = new;
			}
			*hist_index = *hist_head;
		}
	}
}

char	*browse_history_up(t_list **history_index)
{
	char *tmp;

	if (*history_index)
	{
		tmp = (*history_index)->content;
		if ((*history_index)->next != NULL)
			(*history_index) = (*history_index)->next;
		return (tmp);
	}
	return (NULL);
}

char	*browse_history_down(t_list **history_index)
{
	char	*tmp;

	if ((*history_index))
	{
		tmp = (*history_index)->content;
		(*history_index) = (*history_index)->previous;
		return (tmp);
	}
	return (NULL);
}


int		clear_line (t_data *data)
{
	tputs(data->termc->clear_line, 1, putchar_2);
	ft_putstr_fd(PROMPT, STDERR);
	return (1);
}
