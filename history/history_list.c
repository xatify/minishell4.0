/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:08:34 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/02 19:35:00 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_history(t_list **history, t_list *new)
{
	t_list *last;

	if (!(*history))
		(*history) = new;
	else
	{
		(*history)->previous = new;
		new->next = (*history);
		(*history) = new;
	}
}

char	*browse_history_up(t_list *history_index)
{
	if (history_index && history_index->next)
	{
		history_index = history_index->next;
		return (history_index->previous->content);
	}
	return (NULL);
}

char	*brows_history_down(t_list *history_index)
{
	if (history_index && history_index->previous)
	{
		history_index = history_index->previous;
		return (history_index->next->content);
	}
}

