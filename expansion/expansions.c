/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:24:00 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 08:49:47 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*expand(t_list *list, t_data *data, int *error)
{
	t_list			*stack;
	char			**token;
	char			*tkn;

	stack = NULL;
	tkn = (list->content);
	token = &tkn;
	while (**token)
	{
		push(&stack, *(*token)++);
		if (top_stack(&stack) == '\'' || top_stack(&stack) == '\"')
		{
			if (!expand_quotes(&stack, token, data))
				*error = 1;
		}
		else if (!expand_unquoted_token(&stack, token, data, list))
			*error = 1;
		if (*error)
			break ;
	}
	return (handle_expansion(&stack, *error));
}

int			expand_list(t_list *list, t_data *data)
{
	int			error;
	char		*tmp;

	error = 0;
	if (list)
	{
		tmp = expand(list, data, &error);
		if (!error)
		{
			free(list->content);
			if (!tmp)
				list->content = ft_strdup("");
			else
				list->content = tmp;
			return (expand_list(list->next, data));
		}
		else
			return (0);
	}
	return (1);
}

int			expand_redirections(t_list *redirections, t_data *data)
{
	t_list			*tmp_list;
	t_redirection	*redirection;
	int				error;
	char			*tmp;

	if (redirections)
	{
		error = 0;
		tmp_list = NULL;
		redirection = (t_redirection *)redirections->content;
		ft_lstadd_back(&tmp_list, ft_lstnew(ft_strdup(redirection->file)));
		tmp = expand(tmp_list, data, &error);
		if (error || !tmp || (ft_lstsize(tmp_list) > 1))
		{
			ft_putstr_fd(redirection->file, STDERR);
			ft_putstr_fd(AMB_REDIRECT, STDERR);
			ft_lstclear(&tmp_list, free);
			return (0);
		}
		free(redirection->file);
		redirection->file = tmp;
		ft_lstclear(&tmp_list, free);
		return (expand_redirections(redirections->next, data));
	}
	return (1);
}

int			expand_cmd(t_list *cmds, t_data *data)
{
	t_command	*cmd;
	char		*name;
	t_list		*tmp;

	if (cmds)
	{
		cmd = (t_command *)(cmds->content);
		if (expand_list(cmd->name_and_args, data) &&
			expand_redirections(cmd->redirections, data))
		{
			if (cmd->name_and_args)
			{
				name = cmd->name_and_args->content;
				if (name[0] == '\0')
				{
					tmp = cmd->name_and_args->next;
					free(name);
					free(cmd->name_and_args);
					cmd->name_and_args = NULL;
					*(&(cmd->name_and_args)) = tmp;
				}
			}
			return (expand_cmd(cmds->next, data));
		}
		return (0);
	}
	return (1);
}

int			expand_pipeline(t_pipeline *pipline, t_data *data)
{
	return (expand_cmd(pipline->cmds, data));
}
