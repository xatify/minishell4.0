/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:05:12 by keddib            #+#    #+#             */
/*   Updated: 2021/06/27 16:06:01 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirection_error(t_redirection *red, t_list *list, t_list *tokens)
{
	ft_putstr_fd(red->file, STDERR);
	ft_putstr_fd(AMB_REDIRECT, STDERR);
	ft_lstclear(&list, free);
	ft_lstclear(&tokens, free_token);
	return (0);
}

void	reexpand_list(t_list *list, t_list *new_list, t_list *next)
{
	if (new_list)
	{
		ft_lstadd_back(&(new_list), next);
		if (new_list)
		{
			free(list->content);
			list->content = new_list->content;
			list->next = new_list->next;
			free(new_list);
		}
	}
	else
	{
		free(list->content);
		list->content = ft_strdup("");
	}
}
