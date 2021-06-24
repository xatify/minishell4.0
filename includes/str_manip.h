/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manip.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:14:28 by keddib            #+#    #+#             */
/*   Updated: 2021/06/23 17:15:14 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_MANIP_H
# define STR_MANIP_H

/*
** strings manipulation prototypes
*/

char				*ft_strcpy(char *dst, char *src);
int					ft_strlen(char *str);
void				ft_strlcpy(char *dst, char *src, int len);
int					ft_strcmp(char *str1, char *str2);
void				*ft_memset(void	*b, int c, size_t len);
int				is_white_character(char c);
char				*ft_strdup(char *str);
int				is_alpha(char c);
int				is_num(char c);
int				is_underscore(char c);
int				is_identifier(char *str);
int				is_meta(char c);
int					ft_printf(const char *s, ...);
char				*ft_itoa(int i);
char				**ft_split(char const *str, char c);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
char				*ft_strrchr(const char *str, int c);
char				*ft_strchr(const char *str, int c);
int					ft_atoi(const char *str, int *exit);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						int *end_name);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				free_tmp(char **tmp);
int					putchar_2(int c);
int					is_print(char c);

#endif
