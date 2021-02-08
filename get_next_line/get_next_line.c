/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:51:27 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/08 18:31:31 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		ft_bzero(void *str, size_t n)
{
	int i;

	i = -1;
	while (++i < (int)n)
		((unsigned char *)str)[i] = 0;
}

static int	check_buff(char *buff)
{
	int i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	handle_rest(char **tmp, char **line, char **buff, ssize_t b_size)
{
	char *to_free;

	if (b_size == 1)
	{
		(*line) = ft_substr((*tmp), 0, check_buff(*tmp));
		to_free = (*tmp);
		(*tmp) = ft_strdup_((*tmp) + check_buff(*tmp) + 1);
		free(to_free);
		free((*buff));
		return (1);
	}
	else if (b_size == 0)
	{
		*line = ft_strdup_(*tmp);
		free(*tmp);
		*tmp = NULL;
		free(*buff);
		return (0);
	}
	else
	{
		free(*buff);
		free(*tmp);
		return (-1);
	}
}

static int	check_for_error(char **tmp, int fd, char **line, char **buff)
{
	if (fd == -1 || !line || ((*tmp) == NULL && !((*tmp) = ft_strdup_(""))))
		return (1);
	if (!(*buff = malloc(BUFFER_SIZE + 1)))
	{
		free(tmp);
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char *tmp;
	ssize_t		b_size;
	char		*buff;

	if (check_for_error(&tmp, fd, line, &buff))
		return (-1);
	if (check_buff(tmp) >= 0)
		return (handle_rest(&tmp, line, &buff, 1));
	while ((b_size = read(fd, buff, BUFFER_SIZE)) >= 0)
	{
		buff[b_size] = '\0';
		if (check_buff(buff) >= 0)
		{
			(*line) = ft_strjoin_(tmp, ft_substr(buff, 0, check_buff(buff)), 1);
			tmp = ft_strdup_(buff + check_buff(buff) + 1);
			if (tmp[0] == '\0')
				free_tmp(&tmp);
			free(buff);
			return (1);
		}
		tmp = ft_strjoin_(tmp, buff, 0);
		if (b_size == 0)
			break ;
	}
	return (handle_rest(&tmp, line, &buff, b_size));
}
