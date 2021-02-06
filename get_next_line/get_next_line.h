/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:38:30 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/05 18:17:25 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_strdup_(const char *s1);
int		get_next_line(int fd, char **line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_(char const *s1, char const *s2, int i);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *str, size_t n);
size_t	ft_strlen_(const char *str);

#endif
