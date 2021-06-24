/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:19:07 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/23 17:37:12 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redirection	*new_redirection(char *file, int type, t_command *command)
{
	t_redirection	*redirection;
	char		str[10];
	char		*s = &str[0];
	int			fd;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redirection)
		return (NULL);
	if (type == HEREDOC)
	{
		LCG(&s, 9);
		fd = open(str, O_CREAT | O_APPEND | O_WRONLY, 0666);
		if (fd >= 0)
		{
			ft_lstadd_back(&(command->tmp_files), ft_lstnew(ft_strdup(str)));
			s = readline("> ");
			while (s && ft_strcmp(s, file))
			{
				ft_putstr_fd(s, fd);
				ft_putchar_fd('\n', fd);
				free(s);
				s = readline("> ");
			}
			close(fd);
			redirection->file = ft_strdup(str);
			redirection->type = INPUT;
		}
	}
	else
	{
		redirection->file = ft_strdup(file);
		redirection->type = type;
	}
	return (redirection);
}

void	free_redirections(void *redirection)
{
	if (!redirection)
		return ;
	free(((t_redirection *)redirection)->file);
	free(redirection);
}

void	free_tmp_files(void *tmp_file)
{
	unlink(tmp_file);
	free(tmp_file);
}

int	open_file(t_redirection *redirection)
{
	int		fd;

	if (redirection->type == INPUT)
		fd = open(redirection->file, O_RDONLY);
	else if (redirection->type == OUTPUT)
		fd = open(redirection->file, O_TRUNC | O_CREAT | O_RDWR, 0666);
	else
		fd = open(redirection->file, O_APPEND | O_CREAT | O_RDWR, 0666);
	return (fd);
}

void	set_streaming_fds(int *tmp_fd, int fd, int redirection_type)
{
	if (redirection_type == INPUT || redirection_type == HEREDOC)
	{
		if (tmp_fd[0] >= 0)
			close(tmp_fd[0]);
		tmp_fd[0] = fd;
	}
	else
	{
		if (tmp_fd[1] >= 0)
			close(tmp_fd[1]);
		tmp_fd[1] = fd;
	}
}

int	redirect_std(t_command *cmd, int *tmp_fd)
{
	int				fd;
	t_list			*tmp;
	t_redirection	*redirection;

	tmp_fd[0] = -1;
	tmp_fd[1] = -1;
	tmp = cmd->redirections;
	while (tmp)
	{
		redirection = (t_redirection *)tmp->content;
		fd = open_file(redirection);
		if (fd < 0)
		{
			ft_putstr_fd("no such file or directory: ", STDERR);
			ft_putstr_fd(redirection->file, STDERR);
			ft_putchar_fd('\n', STDERR);
			return (0);
		}
		set_streaming_fds(tmp_fd, fd, redirection->type);
		tmp = tmp->next;
	}
	return (1);
}

int	simple_cmd_streaming(t_command *cmd, int *tmp_std)
{
	int		fds[2];
	int		built_in;

	if (cmd->name_and_args)
	{
		built_in = cmd->built_in;
		if (tmp_std)
		{
			tmp_std[0] = -1;
			tmp_std[1] = -1;
		}
	}
	if (!redirect_std(cmd, fds))
		return (1);
	if (fds[0] != -1)
	{
		if (built_in)
			tmp_std[0] = dup(0);
		set_std_stream(0, fds[0]);
		ft_lstclear(&(cmd->tmp_files), free_tmp_files);
	}
	if (fds[1] != -1)
	{
		if (built_in)
			tmp_std[1] = dup(1);
		set_std_stream(1, fds[1]);
	}
	return (0);
}
