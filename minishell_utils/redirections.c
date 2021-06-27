/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:19:07 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/27 17:15:13 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_herdoc(char *file, t_redirection *redirection, t_command *command)
{
	int		fd;
	char	*s;
	char	str[10];

	s = &str[0];
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
		free(s);
		close(fd);
		redirection->file = ft_strdup(str);
		redirection->type = INPUT;
	}
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

	ft_memset(tmp_fd, 255, 8);
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
			ft_memset(tmp_std, 255, 8);
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
